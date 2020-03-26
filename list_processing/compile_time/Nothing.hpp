#pragma once

//
// ... ListProcessing header files
//
#include <list_processing/compile_time/import.hpp>

namespace ListProcessing::CompileTime::Details
{

  struct Nothing
  {

    friend constexpr size_type
    length(Nothing const&)
    {
      return 0;
    }

    // Predicates
    friend constexpr bool
    islist(Nothing const&)
    {
      return true;
    }

    friend constexpr bool
    isnothing(Nothing const&)
    {
      return true;
    }

    friend constexpr bool
    isNull(Nothing const&)
    {
      return true;
    }

    friend constexpr bool
    ispair(Nothing const&)
    {
      return false;
    }

    friend constexpr Nothing
    tail(Nothing const& x)
    {
      return x;
    }

    friend constexpr bool
    operator==(Nothing const&, Nothing const&)
    {
      return true;
    }

    friend constexpr bool
    operator!=(Nothing const&, Nothing const&)
    {
      return !(Nothing{} == Nothing{});
    }

    template<typename T>
    friend constexpr bool
    operator==(Nothing const&, T const&)
    {
      return false;
    }

    template<typename T>
    friend constexpr bool
    operator==(T const&, Nothing const&)
    {
      return false;
    }

    template<typename T>
    friend constexpr bool
    operator!=(Nothing const&, T const&)
    {
      return true;
    }

    template<typename T>
    friend constexpr bool
    operator!=(T const&, Nothing const&)
    {
      return true;
    }

    friend constexpr Nothing
    reverse(Nothing const&)
    {
      return Nothing{};
    }

    template<typename T>
    friend constexpr auto
    rappend(Nothing const&, T const& ys)
    {
      return ys;
    }

    template<typename T>
    friend constexpr auto
    append(Nothing const&, T const& ys)
    {
      return ys;
    }

    template<size_t n>
    friend constexpr auto
    take(Nat<n>, Nothing const&)
    {
      return Nothing{};
    }

    template<size_t n>
    friend constexpr auto
    drop(Nat<n>, Nothing const&)
    {
      return Nothing{};
    }

    template<typename F, typename T>
    friend constexpr auto
    foldl(F, T const& init, Nothing const&)
    {
      return init;
    }

    template<typename F, typename... Ts>
    friend constexpr auto
    app_(F f, Nothing const&, Ts const&... xs)
    {
      return f(xs...);
    }

    template<typename F>
    friend constexpr auto
    app(F f, Nothing const&)
    {
      return f();
    }

  }; // end of struct Nothing

  constexpr bool length_(Type<Nothing>)
  {
    return 0;
  }

  template<typename T>
  constexpr bool isListType(Type<T>)
  {
    return false;
  }

  constexpr bool isListType(Type<Nothing>)
  {
    return true;
  }

  constexpr Nothing nothing{};
  constexpr Nothing nil = nothing;

  constexpr Nothing
  list()
  {
    return {};
  }

} // end of namespace ListProcessing::CompileTime::Details
