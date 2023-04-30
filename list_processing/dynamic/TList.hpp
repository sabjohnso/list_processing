#pragma once

//
// ... List Processing header files
//
#include <list_processing/dynamic/Value.hpp>
#include <list_processing/dynamic/import.hpp>

namespace ListProcessing::Dynamic::Details {

  template<typename T>
  class Construct;

  struct Nothing
  {
  public:
    template<typename T>
    constexpr auto
    cons(T&& x) const
    {
      return Construct<decay_t<T>>{std::forward<T>(x), *this};
    }

    template<typename T>
    friend constexpr auto
    cons(T&& x, Nothing const& nothing)
    {
      return nothing.cons(std::forward<T>(x));
    }

    friend ostream&
    operator<<(ostream& os, Nothing const&)
    {
      return os << "<>";
    }
  } constexpr nothing{};

  template<typename T>
  class Construct
  {
    using value_type = T;
    using const_reference = const value_type&;

    using shared = Shared<value_type>;
    struct list_pointer : shared_ptr<Construct>
    {
      using base = shared_ptr<Construct>;
      using base::base;

      list_pointer(shared_ptr<Construct> const& input)
        : base(input)
      {}

      friend bool
      operator==(list_pointer px, list_pointer py)
      {
        return px->car() == py->car() && px->cdr() == py->cdr();
      }

      friend bool
      operator!=(list_pointer px, list_pointer py)
      {
        return !(px == py);
      }

      template<typename U>
      friend bool
      operator==(list_pointer, U&&)
      {
        return false;
      }

      template<typename U>
      friend bool
      operator!=(list_pointer, U&&)
      {
        return true;
      }
    };

  public:
    struct datum_type : variant<shared, list_pointer, Nothing>
    {
      using base = variant<shared, list_pointer, Nothing>;
      using base::base;

      friend bool
      operator==(datum_type x, datum_type y)
      {
        if (holds_alternative<shared>(x) && holds_alternative<shared>(y)) {
          return get<shared>(x) == get<shared>(y);
        } else if (
          holds_alternative<list_pointer>(x) &&
          holds_alternative<list_pointer>(y)) {
          return get<list_pointer>(x) == get<list_pointer>(y);
        } else if (
          holds_alternative<Nothing>(x) && holds_alternative<Nothing>(y)) {
          return true;
        } else {
          return false;
        }
      }

      bool
      ispair() const
      {
        return holds_alternative<list_pointer>(*this);
      }

      friend bool
      ispair(const datum_type& x)
      {
        return x.ispair();
      }

      auto
      car() const
      {
        return get<list_pointer>(*this)->car();
      }

      friend auto
      car(datum_type const& x)
      {
        return x.car();
      }

      friend bool
      operator!=(datum_type x, datum_type y)
      {
        return !(x == y);
      }

      friend ostream&
      operator<<(ostream& os, datum_type x)
      {
        if (holds_alternative<shared>(x)) {
          return os << get<shared>(x);
        } else if (holds_alternative<list_pointer>(x)) {
          return os << get<list_pointer>(x);
        } else {
          return os << nothing;
        }
      }
    };

  public:
    Construct(datum_type car, datum_type cdr)
      : ptr(make_shared<Kernel>(car, cdr))
    {}

    datum_type
    car() const
    {
      return ptr->car;
    }

    friend datum_type
    car(Construct<T> xs)
    {
      return xs.car();
    }

    datum_type
    cdr() const
    {
      return ptr->cdr;
    }

    friend datum_type
    cdr(Construct<T> xs)
    {
      return xs.cdr();
    }

    friend ostream&
    operator<<(ostream& os, Construct xs)
    {
      os << xs.car() << " " << xs.cdr();
      return os;
    }

    template<typename U>
    auto
    cons(U&& x) const
    {
      return Construct(
        std::forward<U>(x), list_pointer(make_shared<Construct>(*this)));
    }

    template<typename U>
    friend auto
    cons(U&& x, Construct<T> xs)
    {
      return xs.cons(std::forward<U>(x));
    }

  private:
    struct Kernel
    {
      datum_type car;
      datum_type cdr;

      Kernel(Kernel const&) = delete;
      Kernel(Kernel&& input) = default;

      Kernel(datum_type input_car, datum_type input_cdr)
        : car(input_car)
        , cdr(input_cdr)
      {}
    };

    using kernel_pointer = shared_ptr<Kernel>;
    kernel_pointer ptr;
  };

  template<typename... Ts>
  struct ConstructValueType
  {
    template<typename... Us>
    struct Aux;

    template<typename T, typename... Us>
    struct Aux<Nothing, Construct<T>, Us...> : Aux<T, Us...>
    {};

    template<typename T, typename... Us>
    struct Aux<Nothing, T, Us...> : Aux<T, Us...>
    {};

    template<typename T, typename... Us>
    struct Aux<T, Nothing, Us...> : Aux<T, Us...>
    {};

    template<typename T, typename... Us>
    struct Aux<T, Construct<Nothing>, Us...> : Aux<T, Us...>
    {};

    template<typename T, typename U, typename... Us>
    struct Aux<T, Construct<U>, Us...> : Aux<common_type_t<T, U>, Us...>
    {};

    template<typename T, typename U, typename... Us>
    struct Aux<T, U, Us...> : Aux<common_type_t<T, U>, Us...>
    {};

    template<typename T>
    struct Aux<T>
    {
      using type = T;
    };

    using type = typename Aux<Nothing, Ts...>::type;
  };

  struct
  {
    constexpr auto
    operator()() const
    {
      return nothing;
    }

    template<typename T, typename... Ts>
    auto
    operator()(T&& x, Ts&&... xs) const
    {
      using U = typename ConstructValueType<decay_t<T>, decay_t<Ts>...>::type;
      return cons(U(std::forward<T>(x)), (*this)(U(std::forward<Ts>(xs))...));
    }

  } constexpr tlist{};

} // end of namespace ListProcessing::Dynamic::Details
