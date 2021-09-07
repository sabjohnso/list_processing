#pragma once

//
// ... List Processing header files
//
#include <list_processing/dynamic/hash_table/Bin.hpp>

namespace ListProcessing::Dynamic::Details {

  template<typename Key, typename Mapped, size_type BinSizeExponent>
  class StorageBranch : public enable_shared_from_this
  {
    using storage_branch_pointer = shared_ptr<StorageBranch>;

    using key_type = Key;
    using key_const_reference = key_type const&;

    using mapped_type = Mapped;
    using mapped_const_reference = mapped_type const&;

    using value_type = pair<key_type, mapped_type>;
    using const_reference = value_type const&;

    static constexpr size_type bin_size_exponent = BinSizeExponent;
    static constexpr size_type bin_size = 1 < bin_size_exponent;
    using bin_type = Bin<key_type, mapped_type, bin_size_exponent>;

    using branch_type = array<StorageBranch, bin_size>;

  public:
    mapped_const_reference
    get(key_const_reference key, index_type index) const
    {
      index_type local_index = index & bin_index_mask;
      if (indicator[local_index]) {
        if (holds_alternative<bin_pointer>(storage)) {
          using std::get;
          return get<bin_pointer>(storage)->get(key, index & bin_index_mask);
        } else {
          assert(holds_alternative<branch_pointer>(storage));
          return get<branch_pointer>(storage)->get(
            key, index >> bin_size_exponent);
        }
      } else {
        throw logic_error("bad index in branch");
      }
    }

    storage_branch_pointer
    set(key_const_reference key, mapped_const_reference value, index_type index)
    {
      if (holds_alternative<bin_pointer>(storage)) {
        return setBin(key, value, index);
      } else {
        assert(holds_alternative<branch_pointer>(storage));
        return setBranch(key, value, index);
      }
    }

  private:
    storage_branch_pointer
    setBin(
      key_const_reference key,
      mapped_const_reference value,
      index_type index) const
    {
      assert(holds_alternative<bin_pointer>(storage));
      using std::get;

      lock_guard lock(mex);

      storage_branch_pointer result = nullptr;
      switch (get<bin_pointer>(storage)) {
        case injection:
          result = make_shared<StorageBranch>();
          break;
        case mutation:
          result = mutate();
        case collision:
          result = fracture();
          break;
        case noop:
          result = shared_from_this();
          break;
      }
      return result;
    }

    storage_branch_pointer
    inject(index_type index) const
    {
      assert(!indicator[index]);
      return make_shared<StorageBranch>(
        storage, indicator & 1 << (index & bin_index_mask));
    }

    storage_branch_pointer
    mutate(
      key_const_reference key,
      mapped_const_reference value,
      index_type index) const
    {
      using std::get;

      auto bin = get<bin_pointer>(storage);

      auto result = make_shared<StorageBranch>();
      for (auto i = 0; i < bin_size; ++i) {
        if (indicator[i] && i != index) {
          result->setPair(bin->getPair);
        }
      }
      auto response = result.set(key, value, index);
      assert(response == BinSetResponse::injection);

      return result;
    }

    storage_branch_pointer
    setBranch(
      key_const_reference key,
      mapped_const_reference value,
      index_type index) const
    {}

  public:
    storage_branch_pointer
    remove(
      key_const_reference key,
      mapped_const_reference value,
      index_type index)
    {}

  private:
    using storage_type = variant<bin_pointer, branch_pointer>;
    using indicator_type = bitset<bin_size>;
    storage_type storage;
    indicator_type indicator;
    mutex mex;

  }; // end of class StorageBranch

} // end of namespace ListProcessing::Dynamic::Details
