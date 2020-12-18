#pragma once

namespace ListProcessing::Dynamic::Details
{

  template<typename T>
  constexpr auto
  pipe(T&& x)
  {
    return std::forward<T>(x);
  }

  template<typename T, typename F, typename... Fs>
  constexpr auto
  pipe(T const& x, F f, Fs... fs)
  {
    return pipe(f(x), fs...);
  }

  template<typename T, typename F, typename ... Fs>
  constexpr auto
  fanout(T&& x, F&& f, Fs&& ... fs){
    return list(f(x), fs(x) ...);
  }
} // end of namespace ListProcessing::Dynamic::Details
