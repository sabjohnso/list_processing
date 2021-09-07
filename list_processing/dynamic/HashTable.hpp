#pragma once

//
// ... List Processing header files
//
#include <list_processing/dynamic/AList.hpp>
#include <list_processing/dynamic/Bucket.hpp>
#include <list_processing/dynamic/Stream.hpp>
#include <list_processing/dynamic/hash_table/utility.hpp>
#include <list_processing/dynamic/import.hpp>

namespace ListProcessing::Dynamic::Details {

  template<
    typename Key,
    typename Mapped,
    size_type BinSizeExponent =
      Config::Info::Parameters::default_bin_size_exponent>
  class HashTable
  {

    static_assert(BinSizeExponent > 0, "BinSizeExponent must be positive");

  public:
    using key_type = Key;
    using key_const_reference = key_type const&;
    using mapped_type = Mapped;
    using mapped_const_reference = mapped_type&;
    using value_type = pair<key_type, mapped_type>;
    using const_reference = value_type const&;

    constexpr static size_type bin_size_exponent = BinSizeExponent;
    constexpr static size_type bin_size = 1 << bin_size_exponent;

    HashTable() = default;
    HashTable(HashTable const&) = default;

    HashTable(initializer_list<value_type> const&)
      : pkernel(make_shared<Kernel>())
    {}

    bool
    hasData() const
    {
      return bool(pkernel);
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

    mapped_const_reference get(key_const_reference) const
    {
      throw logic_error("not implemented");
      return *this;
    }

    mapped_const_reference
    forceGet(key_const_reference, mapped_const_reference alternate) const
    {
      throw logic_error("not implemented");
      return alternate;
    }

    optional<mapped_type> maybeGet(key_const_reference) const
    {
      throw logic_error("not implemented");
      return {};
    }

    HashTable set(key_const_reference, mapped_const_reference) const
    {
      throw logic_error("not implemented");
      return *this;
    }

    HashTable remove(key_const_reference) const
    {
      throw logic_error("not implemented");
      return *this;
    }

    AList<key_type, mapped_type>
    toAList() const
    {
      throw logic_error("not implemented");
      return {};
    }

    Stream<value_type>
    toStream() const
    {
      throw logic_error("not implemented");
      return {};
    }

    List<key_type>
    keys() const
    {
      throw logic_error("not implemented");
      return {};
    }

    List<mapped_type>
    values() const
    {
      throw logic_error("not implemented");
      return {};
    }

    Stream<key_type>
    inKeys() const
    {
      throw logic_error("not implemented");
      return {};
    }

    Stream<mapped_type>
    inValues() const
    {
      throw logic_error("not implemented");
      return {};
    }

    size_type
    size() const
    {
      throw logic_error("not implemented");
      return 0;
    }

  private:
    class Kernel
    {};

    using kernel_pointer = shared_ptr<Kernel>;
    kernel_pointer pkernel;
  }; // end of class HasData

  template<typename Key, typename Mapped>
  HashTable(initializer_list<pair<Key, Mapped>>) -> HashTable<Key, Mapped>;

} // end of namespace ListProcessing::Dynamic::Details
