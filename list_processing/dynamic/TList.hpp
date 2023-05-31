#pragma once

//
// ... List Processing header files
//
#include <list_processing/dynamic/Value.hpp>
#include <list_processing/dynamic/import.hpp>

namespace ListProcessing::Dynamic::Details {

  template<typename T>
  class Construct {
  public:
    using slot_base = variant<Shared<T>, Construct>;

    struct Slot : slot_base {
      using slot_base::slot_base;
      friend bool ispair(Slot x){
	return holds_alternative<Construct>(x)
	  ? ispair(std::get<Construct>(x))
	  : false;
      }

      friend bool
      operator==(Slot x, Slot y){
	return holds_alternative<Construct>(x) && holds_alternative<Construct>(y)
	  ? std::get<Construct>(x) == std::get<Construct>(x)
	  : ((holds_alternative<Shared<T>>(x) && holds_alternative<Shared<T>>(y))
	     ? std::get<Shared<T>>(x) == std::get<Shared<T>>(x)
	     : false);
      }

      friend auto
      car(Slot x){
	return holds_alternative<Construct>(x)
	  ? car(std::get<Construct>(x))
	  : throw logic_error("Shared value does not have a car");
      }

      friend auto
      cdr(Slot x){
	return holds_alternative<Construct>(x)
	  ? cdr(std::get<Construct>(x))
	  : throw logic_error("Shared value does not have a car");
      }

      friend auto
      cadr(Slot x){
	return car(cdr(x));
      }
    };
  private:



    struct Kernel {

      Kernel(const Kernel&) = delete;

      Kernel(Kernel&& input)
	: car(std::move(input.car))
	, cdr(std::move(input.cdr)){
      }

      template<convertible_to<Slot> U, convertible_to<Slot> V>
      Kernel(U&& car, V&& cdr)
	: car(std::forward<U>(car))
	, cdr(std::forward<V>(cdr)){
      }

      Slot car;
      Slot cdr;

    }; // end of struct Kernel

    using kernel_pointer = shared_ptr<const Kernel>;

    kernel_pointer ptr{};

  public:

    using value_type = T;

    Construct() = default;

    Construct(const Construct&) = default;

    template<
      convertible_to<Slot> U,
      convertible_to<Slot> V>
    Construct(U&& car, V&& cdr) : ptr(make_shared<Kernel>(std::forward<U>(car), std::forward<V>(cdr))){
    }

    static const Construct nil;

    friend bool
    operator ==(Construct xs, Construct ys){
      return bool(xs.ptr) && bool(ys.ptr)
	? car(xs) == car(ys) && cdr(xs) == cdr(ys)
	: (! bool(xs.ptr)) && (! bool(ys.ptr));
    }

    friend auto
    car(Construct xs){
      return bool(xs.ptr)
	? xs.ptr->car
	: throw logic_error("Cannot access the head of an empty list");
    }

    friend auto
    cdr(Construct xs){
      return bool(xs.ptr)
	? xs.ptr->cdr
	: Slot{xs};
    }
    friend auto
    cadr(Construct xs){
      return car(cdr(xs));
    }

    friend auto
    ispair(Construct xs){
      return bool(xs.ptr);
    }
  private:

  }; // end of class Construct

  template<typename T>
  const Construct<T> Construct<T>::nil = Construct<T>{};

  struct TCons {

    template<typename T>
    auto
    operator()(Shared<T> x, Shared<T> y) const {
      return Construct<T>{x, y};
    }

    template<typename T>
    auto
    operator()(Shared<T> x, Construct<T> y) const {
      return Construct{x, y};
    }

    template<typename T>
    auto
    operator()(Construct<T> x, Shared<T> y) const {
      return Construct<T>{x, y};
    }


    template<typename T>
    auto
    operator()(Construct<T> x, Construct<T> y) const {
      return Construct<T>{x, y};
    }

    template<typename T>
    auto
    operator()(T x, Construct<T> y) const {
      return Construct<T>{ Shared<T>{x}, y };
    }

    template<typename T>
    auto
    operator()(T x, Shared<T> y) const {
      return Construct<T>{ Shared<T>{x}, y };
    }

    template<typename T>
    auto
    operator()(Shared<T> x, T y) const {
      return Construct<T>{ x, Shared<T>{y} };
    }


    template<typename T>
    auto
    operator()(Construct<T> x,  T y) const {
      return Construct<T>{ x, Shared<T>{y} };
    }

  } constexpr tcons{};


  struct TListConstructor {
    auto
    operator()() const {
      return Construct<int>{};
    }

    template<typename T>
    auto
    operator()(Shared<T> x) const {
      return tcons(x, Construct<T>::nil);
    }

    template<typename T>
    auto
    operator()(Construct<T> x) const {
      return tcons(x, Construct<T>::nil);
    }

    template<typename T>
    auto
    operator()(T x) const {
      return tcons(x, Construct<T>::nil);
    }

    template<typename T1, typename T2, typename ... Ts>
    auto
    operator()(T1 x1, T2 x2, Ts ... xs) const {
      return tcons(x1, (*this)(x2, xs ...));
    }

  } constexpr tlist{};



} // end of namespace ListProcessing::Dynamic::Details
