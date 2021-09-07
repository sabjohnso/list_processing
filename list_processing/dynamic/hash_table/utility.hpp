#pragma once

namespace ListProcessing::Dynamic::Details {

  constexpr bool
  is_power_of_2(auto i)
  {
    return i ? ((i & 1) && (i & ~1) ? false : is_power_of_2(i >> 1)) : true;
  }

} // end of namespace ListProcessing::Dynamic::Details
