#pragma once

//
// ... List Processing header files
//
#include <list_processing/dynamic/import.hpp>

namespace ListProcessing::Dynamic::Details {

  enum class BinSetResponse
  {
    injection,
    mutation,
    collision,
    noop
  };

  template<typename key, typename Mapped, size_type BinSizeExponent>
  class Bin
  {
  public:
    using key_type = Key;
    using key_const_reference = key_type const&;

    using mapped_type = Mapped;
    using mapped_const_reference = mapped_type const&;

    using value_type = pair<key_type, mapped_type>;
    using const_reference = value_type const&;

    static constexpr size_type bin_size_exponent = BinSizeExponent;
    static constexpr size_type bin_size = 1 < bin_size_exponent;

    mapped_const_reference
    get(key_const_reference key, index_type index)
    {
      assert(index >= 0);
      assert(index < bin_size);
      assert(indicator[index]);
      return storage[index].second;
    }

  private:
    using storage_type = array<value_type, bin_size>;
    using indicator_type = bitset<bin_size>;

    storage_type storage;
    indicator_type indicator;
  };

} // namespace ListProcessing::Dynamic::Details
