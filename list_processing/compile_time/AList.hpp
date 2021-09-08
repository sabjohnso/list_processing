#pragma once

//
// ... List Processing header files
//
#include <list_processing/compile_time/Cell.hpp>
#include <list_processing/compile_time/Nothing.hpp>
#include <list_processing/compile_time/import.hpp>

namespace ListProcessing::CompileTime::Details {

  template<typename T>
  class AList;

  template<typename K, typename V, typename Tail>
  class AList<Cell<pair<K, V>, Tail>>
  {
    using DataType = Cell<pair<K, V>, Tail>;

    DataType data;

  public:
    constexpr AList() = delete;
    constexpr AList(DataType const& input)
      : data(input)
    {}
    constexpr AList(DataType&& input)
      : data(move(input))
    {}

    //          _
    //  ___ ___| |_
    // (_-</ -_)  _|
    // /__/\___|\__|
    template<typename K2, typename V2>
    constexpr auto
    set(K2 const& key, V2 const& value) const&
    {
      using NewDataType = decltype(cons(pair(key, value), data));
      return AList<NewDataType>(cons(pair(key, value), data));
    }

    template<typename K2, typename V2>
    friend constexpr auto
    set(K2 const& key, V2 const& value, AList const& xs)
    {
      return xs.set(key, value);
    }

    //                    _
    //  _  _ _ _  ___ ___| |_
    // | || | ' \(_-</ -_)  _|
    //  \_,_|_||_/__/\___|\__|
    constexpr auto
    unset(K const&) const
    {
      return AList<Tail>(tail(data));
    }

    template<typename U>
    constexpr auto
    unset(U const& key) const
    {
      return AList<Tail>(tail(data))
        .unset(key)
        .set(head(data).first, head(data).second);
    }

    template<typename U>
    friend constexpr auto
    unset(U const& key, AList const& xs)
    {
      return xs.unset(key);
    }

    //  _ _ ___ _ __  _____ _____
    // | '_/ -_) '  \/ _ \ V / -_)
    // |_| \___|_|_|_\___/\_/\___|
    //
    constexpr auto
    remove(K const& key) const
    {
      return AList<Tail>(tail(data)).remove(key);
    }

    template<typename U>
    constexpr auto
    remove(U const& key) const
    {
      return AList<Tail>(tail(data))
        .remove(key)
        .set(head(data).first, head(data).second);
    }

    template<typename U>
    friend constexpr auto
    remove(U const& key, AList const& xs)
    {
      return xs.remove(key);
    }

    //  _            _  __
    // | |_  __ _ __| |/ /___ _  _
    // | ' \/ _` (_-< ' </ -_) || |
    // |_||_\__,_/__/_|\_\___|\_, |
    //                        |__/
    constexpr bool
    hasKey(K const&) const
    {
      return true;
    }

    template<typename T>
    constexpr bool
    hasKey(T const& key) const
    {
      return AList<Tail>(tail(data)).hasKey(key);
    }

    template<typename T>
    friend bool
    hasKey(T const& key, AList const& xs)
    {
      return xs.hasKey(key);
    }

    //   __                 ___     _
    //  / _|___ _ _ __ ___ / __|___| |_
    // |  _/ _ \ '_/ _/ -_) (_ / -_)  _|
    // |_| \___/_| \__\___|\___\___|\__|

    template<typename T>
    constexpr auto
    forceGet(K const&, T const&) const
    {
      return head(data).second;
    }

    template<typename U, typename T>
    constexpr auto
    forceGet(U const& key, T const& alternative) const
    {
      return AList<Tail>(tail(data)).forceGet(key, alternative);
    }

    template<typename U, typename T>
    friend constexpr auto
    forceGet(U const& key, T const& alternative, AList const& xs)
    {
      return xs.forceGet(key, alternative);
    }

    //  _             ___     _
    // | |_ _ _ _  _ / __|___| |_
    // |  _| '_| || | (_ / -_)  _|
    //  \__|_|  \_, |\___\___|\__|
    //          |__/
    constexpr auto
    tryGet(K const&) const
    {
      return head(data).second;
    }

    template<typename U>
    constexpr auto
    tryGet(U const& key) const
    {
      return AList<Tail>(tail(data)).tryGet(key);
    }

    template<typename U>
    friend constexpr auto
    tryGet(U const& key, AList const& xs)
    {
      return xs.tryGet(key);
    }

    //  _            ___       _
    // | |_  __ _ __|   \ __ _| |_ __ _
    // | ' \/ _` (_-< |) / _` |  _/ _` |
    // |_||_\__,_/__/___/\__,_|\__\__,_|
    //
    constexpr bool
    hasData() const
    {
      return true;
    }

    friend constexpr bool
    hasData(AList const& xs)
    {
      return xs.hasData();
    }

    //  _    ___            _
    // (_)__| __|_ __  _ __| |_ _  _
    // | (_-< _|| '  \| '_ \  _| || |
    // |_/__/___|_|_|_| .__/\__|\_, |
    //                |_|       |__/
    constexpr bool
    isEmpty() const
    {
      return !hasData();
    }

    friend constexpr bool
    isEmpty(AList const& xs)
    {
      return xs.isEmpty();
    }

    constexpr auto
    keys() const
    {
      return mapList([](auto kv) { return kv.first; }, data);
    }

    friend constexpr auto
    keys(AList const& xs)
    {
      return xs.keys();
    }

    constexpr auto
    vals() const
    {
      return mapList([](auto kv) { return kv.second; }, data);
    }

    friend constexpr auto
    vals(AList const& xs)
    {
      return xs.vals();
    }

    constexpr auto
    toList() const
    {
      return data;
    }

    friend constexpr auto
    toList(AList const& xs)
    {
      return xs.toList();
    }

    ////////////////////////////////////////////////////////////////////////

    friend ostream&
    operator<<(ostream& os, AList const& xs)
    {
      auto printpair = [&](auto const& x) {
        os << "(" << x.first << " . " << x.second << ")";
      };
      os << "AList(";
      printpair(head(xs.data));
      doList(tail(xs.data), [&](auto const& x) {
        os << " ";
        printpair(x);
      });

      os << ")";
      return os;
    }

  }; // end of class AList<Cell<pair<K,V>, Tail>>

  template<>
  class AList<Nothing>
  {
    using DataType = Nothing;

    DataType data;

  public:
    constexpr AList(){};
    constexpr AList(Nothing const&){};
    constexpr AList(Nothing&&){};

    //          _
    //  ___ ___| |_
    // (_-</ -_)  _|
    // /__/\___|\__|
    template<typename K, typename V>
    constexpr auto
    set(K const& key, V const& value) const
    {
      using NewDataType = Cell<pair<K, V>, Nothing>;
      return AList<NewDataType>(cons(pair(key, value), nothing));
    }

    template<typename K, typename V>
    friend constexpr auto
    set(K const& key, V const& value, AList const& xs)
    {
      return xs.set(key, value);
    }

    //                    _
    //  _  _ _ _  ___ ___| |_
    // | || | ' \(_-</ -_)  _|
    //  \_,_|_||_/__/\___|\__|
    template<typename K>
    constexpr AList
    unset(K const&) const
    {
      return *this;
    }

    template<typename K>
    friend constexpr AList
    unset(K const& key, AList const& xs)
    {
      return xs.unset(key);
    }

    //  _ _ ___ _ __  _____ _____
    // | '_/ -_) '  \/ _ \ V / -_)
    // |_| \___|_|_|_\___/\_/\___|
    template<typename K>
    constexpr AList
    remove(K const&) const
    {
      return *this;
    }

    template<typename K>
    friend constexpr AList
    remove(K const& key, AList const& xs)
    {
      return xs.remove(key);
    }

    //  _            _  __
    // | |_  __ _ __| |/ /___ _  _
    // | ' \/ _` (_-< ' </ -_) || |
    // |_||_\__,_/__/_|\_\___|\_, |
    //                        |__/
    template<typename K>
    constexpr bool
    hasKey(K const&) const
    {
      return false;
    }

    template<typename K>
    friend constexpr bool
    hasKey(K const& key, AList const& xs)
    {
      return xs.hasKey(key);
    }

    //   __                 ___     _
    //  / _|___ _ _ __ ___ / __|___| |_
    // |  _/ _ \ '_/ _/ -_) (_ / -_)  _|
    // |_| \___/_| \__\___|\___\___|\__|
    template<typename K, typename V>
    constexpr V
    forceGet(K const&, V const& alternative) const
    {
      return alternative;
    }

    template<typename K, typename V>
    friend constexpr V
    forceGet(K const& key, V const& alternative, AList const& xs)
    {
      return xs.forceGet(key, alternative);
    }

    //  _            ___       _
    // | |_  __ _ __|   \ __ _| |_ __ _
    // | ' \/ _` (_-< |) / _` |  _/ _` |
    // |_||_\__,_/__/___/\__,_|\__\__,_|
    constexpr bool
    hasData() const
    {
      return false;
    }

    friend constexpr bool
    hasData(AList const& xs)
    {
      return xs.hasData();
    }

    //  _    ___            _
    // (_)__| __|_ __  _ __| |_ _  _
    // | (_-< _|| '  \| '_ \  _| || |
    // |_/__/___|_|_|_| .__/\__|\_, |
    //                |_|       |__/
    constexpr bool
    isEmpty() const
    {
      return !hasData();
    }

    friend constexpr bool
    isEmpty(AList const& xs)
    {
      return xs.isEmpty();
    }

    constexpr auto
    keys() const
    {
      return mapList([](auto kv) { return kv.first; }, data);
    }

    friend constexpr auto
    keys(AList const& xs)
    {
      return xs.keys();
    }

    constexpr auto
    vals() const
    {
      return mapList([](auto kv) { return kv.second; }, data);
    }

    friend constexpr auto
    vals(AList const& xs)
    {
      return xs.vals();
    }

    constexpr auto
    toList() const
    {
      return data;
    }

    friend constexpr auto
    toList(AList const& xs)
    {
      return xs.toList();
    }

    ////////////////////////////////////////////////////////////////////////

    friend ostream&
    operator<<(ostream& os, AList const&)
    {
      return os << "empty_alist";
    }

  }; // end of class AList<Nothing>

  template<typename K, typename V, typename Tail>
  AList(Cell<pair<K, V>, Tail>) -> AList<Cell<pair<K, V>, Tail>>;

  template<typename T>
  concept EmbelishedType = !is_same_v<T, decay_t<T>>;

  template<typename K, typename Table>
  struct HasKeyByType;

  template<EmbelishedType K, EmbelishedType Table>
  struct HasKeyByType<K, Table> : HasKeyByType<decay_t<K>, decay_t<Table>>
  {};

  template<EmbelishedType K, typename Table>
  struct HasKeyByType<K, Table> : HasKeyByType<decay_t<K>, Table>
  {};

  template<typename K, EmbelishedType Table>
  struct HasKeyByType<K, Table> : HasKeyByType<K, decay_t<Table>>
  {};

  template<typename U>
  struct HasKeyByType<U, AList<Nothing>> : false_type
  {};

  template<typename K, typename V, typename Tail>
  struct HasKeyByType<K, AList<Cell<pair<K, V>, Tail>>> : true_type
  {};

  template<typename U, typename K, typename V, typename Tail>
  struct HasKeyByType<U, AList<Cell<pair<K, V>, Tail>>>
    : HasKeyByType<U, AList<Tail>>
  {};

  template<typename K, typename Table>
  constexpr bool hasKeyByType = HasKeyByType<decay_t<K>, decay_t<Table>>::value;

  constexpr AList<Nothing> empty_alist{};

  template<typename... Ts>
  constexpr auto
  alist(Ts&&... xs)
  {
    return AList(list(forward<Ts>(xs)...));
  }

} // end of namespace ListProcessing::CompileTime::Details
