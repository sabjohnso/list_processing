#pragma once

//
// ... List Processing header files
//
#include <list_processing/config.hpp>
#include <list_processing/dynamic/import.hpp>

namespace ListProcessing::Dynamic::Details {

  constexpr bool
  is_power_of_2(auto i)
  {
    return i ? ((i & 1) && (i & ~1) ? false : is_power_of_2(i >> 1)) : true;
  }

  enum class BucketResponse
  {
    injection,
    mutation,
    collision

  };

  template<
    typename Key,
    typename Mapped,
    size_type Extent = Config::Info::Parameters::default_bucket_size>
  class Bucket
  {
  public:
    static constexpr size_type extent = Extent;
    static_assert(is_power_of_2(extent), "Expected extent to be a power of 2");

    using key_type = Key;
    using mapped_type = Mapped;
    using value_type = pair<key_type, mapped_type>;
    using reference = value_type&;
    using const_reference = value_type const&;

    bool
    slotPopulated(index_type index) const
    {
      assert(index >= 0);
      assert(index < extent);
      return indicator[index];
    }

    bool
    slotVacant(index_type index) const
    {
      return !slotPopulated(index);
    }

    BucketResponse
    set(index_type index, const_reference input)
    {
      if (slotVacant(index)) {
        indicator[index] = 1;
        storage[index] = input;
        return BucketResponse::injection;
      } else {
        if (input.first == storage[index].first) {
          return BucketResponse::mutation;
        } else {
          return BucketResponse::collision;
        }
      }
    }

    const_reference
    get(index_type index)
    {
      return storage[index];
    }

  private:
    using storage_type = array<value_type, extent>;
    using indicator_type = bitset<extent>;

    storage_type storage;
    indicator_type indicator;

  }; // end of class Bucket

} // end of namespace ListProcessing::Dynamic::Details
