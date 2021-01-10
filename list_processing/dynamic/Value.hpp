#pragma once

//
// ... List Processing header files
//
#include <list_processing/dynamic/import.hpp>
#include <list_processing/dynamic/concepts.hpp>
#include <list_processing/dynamic/List.hpp>

namespace ListProcessing::Dynamic::Details
{
  template<typename T>
  class Shared
  {
    using value_type = T;
    using const_reference = value_type const&;
    using rvalue_reference = value_type &&;
    using value_pointer  = shared_ptr<const value_type>;
    using const_pointer = const value_type*;
    value_pointer ptr;

  public:
    Shared() = delete;
    Shared(const_reference value) : ptr(value) {}
    Shared(rvalue_reference value) : ptr(make_shared<value_type>(move(value))){}

    explicit
    operator const_reference() const { return *ptr; }

    const_reference
    operator*() const { return *ptr; }

    const_pointer
    operator ->(){ return ptr.get(); }

  }; // end of class Shared

  template<typename T>
  Shared(T value) -> Shared<T>;

  template<typename T>
  Shared(Shared<T> const& input) -> Shared<T>;



  // Addition

  template<AdditiveMagma T>
  Shared<T>
  operator +(Shared<T> x, Shared<T> y){
    return Shared<T>(*x + *y);
  }

  template<AdditiveMagma T>
  Shared<T>
  operator +(Shared<T> x, T const& y){
    return Shared<T>(*x + y);
  }

  template<AdditiveMagma T>
  Shared<T>
  operator +(T const& x, Shared<T> y){
    return Shared<T>(x + *y);
  }


  // Subtraction

  template<AdditiveInverse T>
  Shared<T>
  operator -(Shared<T> x, Shared<T> y){ return Shared<T>(*x - *y); }

  template<AdditiveInverse T>
  Shared<T>
  operator -(Shared<T> x, T const& y){ return Shared<T>(*x - y); }

  template<AdditiveInverse T>
  Shared<T>
  operator -(T const& x, Shared<T> y){ return Shared<T>(x - *y); }



  // Multiplication

  template<MultiplicativeMagma T>
  Shared<T>
  operator *(Shared<T> x, Shared<T> y){ return Shared<T>(*x * *y); }

  template<MultiplicativeMagma T>
  Shared<T>
  operator *(Shared<T> x, T const& y){ return Shared<T>(*x * y); }

  template<MultiplicativeMagma T>
  Shared<T>
  operator *(T const& x, Shared<T> y){ return Shared<T>(x * *y); }


  // Division

  template<MultiplicativeInverse T>
  Shared<T>
  operator /(Shared<T> x, Shared<T> y){ return Shared<T>(*x / *y); }

  template<MultiplicativeInverse T>
  Shared<T>
  operator /(Shared<T> x, T const& y){ return Shared<T>(*x / y); }

  template<MultiplicativeInverse T>
  Shared<T>
  operator /(T const& x, Shared<T> y){ return Shared<T>(x / *y); }


  // Printing

  template<typename Char, Show<Char> T>
  basic_ostream<Char>&
  operator <<(basic_ostream<Char>& os, Shared<T> x){ return os << *x; }



  template<typename T1, typename ... Ts>
  auto
  sharedList(T1&& x, Ts&& ... xs){
    using U = common_type_t<T1, Ts ...>;
    return list(Shared<U>(forward<T1>(x)), Shared<U>(forward<Ts>(xs)) ...);
  }

} // end of namespace ListProcessing::Dynamic::Details
