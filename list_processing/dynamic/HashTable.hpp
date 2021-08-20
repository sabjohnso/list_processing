#pragma once

//
// ... List Processing header files
//
#include <list_processing/dynamic/Bucket.hpp>
#include <list_processing/dynamic/import.hpp>

namespace ListProcessing::Dynamic::Details {

  template<typename Key, typename Value, size_type BinWidth = 32>
  class HashTable
  {
  public:
    using key_type = Key;
    using mapped_type = Value;
    using value_type = pair<key_type, mapped_type>;

    constexpr static size_type bin_width = BinWidth;

    HashTable()
      : ptr(nullptr)
    {}

    HashTable(HashTable const& input)
      : ptr(input.ptr)
    {}

    HashTable(initializer_list<value_type> const& input)
      : ptr(make_shared<Kernel>(initializer_list_to_kernel(input)))
    {}

    bool
    hasData() const
    {
      return bool(ptr);
    }

    friend bool
    hasData(HashTable xs)
    {
      return xs.hasData();
    }

    bool
    isEmpty() const
    {
      return !hasData();
    }

    friend bool
    isEmpty(HashTable xs)
    {
      return xs.isEmpty();
    }

  private:
    class Leaf : enable_shared_from_this<Leaf>
    {
      using element_type = value_type;
      using storage_type = array<value_type, bin_width>;
      using indicator_type = bitset<bin_width>;

    public:
      Leaf()
        : storage{}
        , indicator{}
      {}

      bool
      hasSlot(index_type index) const
      {
        assert(index >= 0);
        assert(index < bin_width);

        return indicator[index];
      }

    private:
      storage_type storage;
      indicator_type indicator;
    };

    class Kernel
    {};

    using kernel_pointer = shared_ptr<const Kernel>;
    kernel_pointer ptr;

    static Kernel
    initializer_list_to_kernel(initializer_list<value_type> const& input)
    {
      auto it = begin(input);
      auto last = end(input);
      std::unique_ptr<Kernel> pkernel;
      while (it != last) {
        // ptable = make_unique<HashTable>(ptable->set(it->first, it->second));
        ++it;
      }
      return *pkernel;
    }

  }; // end of class HasData

} // end of namespace ListProcessing::Dynamic::Details
