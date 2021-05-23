#pragma once

//
// ... List Processing header files
//
#include <list_processing/dynamic/Zipper.hpp>
#include <list_processing/dynamic/import.hpp>

namespace ListProcessing::Dynamic::Details {
  template<typename T>
  class CircularZipper {
  public:
    using value_type      = T;
    using reference       = value_type&;
    using const_reference = value_type const&;

  private:
    using data_type = Zipper<value_type>;

    data_type data;

    friend bool
    ismEpty(CircularZipper xs) {
      return isEmpty(xs.data)
    }

    friend size_type
    period(CircularZipper xs) {
      return length(xs.data);
    }

  }; // end of class CircularZipper
} // end of namespace ListProcessing::Dynamic::Details
