#pragma once

namespace ListProcessing::Dynamic::Details {

  template<typename T, typename F, typename... Fs>
  constexpr auto
  fanout(T&& x, F&& f, Fs&&... fs) {
    return list(f(x), fs(x)...);
  }
} // end of namespace ListProcessing::Dynamic::Details
