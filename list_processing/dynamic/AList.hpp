#pragma once

//
// ... List Processing header files
//
#include <list_processing/dynamic/import.hpp>
#include <list_processing/dynamic/List.hpp>

#include <list_processing/operators.hpp>


namespace ListProcessing::Dynamic::Details
{
  template<typename K, typename T>
  class AList
  {
  public:

    using key_type = K;
    using value_type = T;
    using assoc_type = pair<K,T>;

    AList() : data(nil<assoc_type>) {}
  private:

    using data_type = ListType<assoc_type>;
    data_type data;

  public:

    //          _
    //  ___ ___| |_
    // (_-</ -_)  _|
    // /__/\___|\__|

    /**
     * @brief Return an alist like this alist, with the addition of a the
     * input value associated with the input key.
     */
    AList
    set(K key, T value) const { return AList(cons(pair(key, value), data)); }

    /**
     * @brief Return an `AList` like the input alist, with the addition of a the
     * input value associated with the input key.
     */
    friend AList
    set(K key, T value, AList xs){ return xs.set(key, value); }

    //                    _
    //  _  _ _ _  ___ ___| |_
    // | || | ' \(_-</ -_)  _|
    //  \_,_|_||_/__/\___|\__|
  public:

    /**
     * @brief Remove the first occurace of a value associated with the
     * input key from  this `AList`.
     */
    AList
    unset(K key){
      return AList(data_type(unsetAux(key, data_type::nil, data)));
    }

    /**
     * @brief Remove the first occurance of a value associated with the
     * input key from  the input `AList`.
     */
    friend AList
    unset(K key, AList xs){
      return AList(data_type(unsetAux(key, data_type::nil, xs.data)));
    }

  private:

    static Trampoline<data_type>
    unsetAux(K key, data_type accum, data_type xs){
      using tramp = Trampoline<data_type>;
      return xs.hasData()
        ? (head(xs).first == key
           ? tramp(rappend(accum, tail(xs)))
           : tramp([=]{ return unsetAux(key, cons(head(xs), accum), tail(xs)); }))
        : tramp(reverse(accum));
    }

    //  _ _ ___ _ __  _____ _____
    // | '_/ -_) '  \/ _ \ V / -_)
    // |_| \___|_|_|_\___/\_/\___|
  public:

    /**
     * @brief Remove the all occurances of a values associated with the
     * input key from this `AList`.
     */
    AList
    remove(K key) const {
      return AList(data_type(removeAux(key, data_type::nil, data)));
    }

    /**
     * @brief Remove the all occurances of a values associated with the
     * input key from  the input `AList`.
     */
    friend AList
    remove(K key, AList xs){
      return AList(data_type(removeAux(key, data_type::nil, xs.data)));
    }

  private:

    static Trampoline<data_type>
    removeAux(K key, data_type accum, data_type xs){
      using tramp = Trampoline<data_type>;
      return xs.hasData()
        ? (head(xs).first == key
           ? tramp([=]{ return removeAux(key, accum, tail(xs)); })
           : tramp([=]{ return removeAux(key, cons(head(xs), accum), tail(xs)); }))
        : tramp(reverse(accum));
    }

    //  _            _  __
    // | |_  __ _ __| |/ /___ _  _
    // | ' \/ _` (_-< ' </ -_) || |
    // |_||_\__,_/__/_|\_\___|\_, |
    //                        |__/
  public:

    /**
     * @brief Return `true` if this `AList` has the input key and
     * `false` if it does not.
     */
    bool
    hasKey(K key) const {
      return bool(hasKeyAux(key, data));
    }

    /**
     * @brief Return `true` if the input `AList` has the input key and
     * `false` if it does not.
     */
    friend bool
    hasKey(K key, AList xs){
      return bool(hasKeyAux(key, xs.data));
    }

  private:

    static Trampoline<bool>
    hasKeyAux(K key, data_type xs){
      using tramp = Trampoline<bool>;
      return xs.hasData()
        ? (head(xs).first == key
           ? tramp(true)
           : tramp([=]{ return hasKeyAux(key, tail(xs)); }))
        : tramp(false);
    }

    //   __                 ___     _
    //  / _|___ _ _ __ ___ / __|___| |_
    // |  _/ _ \ '_/ _/ -_) (_ / -_)  _|
    // |_| \___/_| \__\___|\___\___|\__|
  public:

    /**
     * @brief Return the value associated with an input key in this `AList`,
     * or and alternate value if the `AList` does not have a value associated
     * with the input key.
     */
    T
    forceGet(K key, T alternate) const {
      return T(forceGetAux(key, alternate, data));
    }

    /**
     * @brief Return the value associated with an input key in the input `AList`,
     * or and alternate value if the `AList` does not have a value associated with
     * the input key.
     */
    friend T
    forceGet(K key, T alternate, AList xs){
      return T(forceGetAux(key, alternate, xs.data));
    }

  private:

    static Trampoline<T>
    forceGetAux(K key, T alternate, data_type xs){
      using tramp = Trampoline<T>;
      return xs.hasData()
        ? (head(xs).first == key
           ? tramp(head(xs).second)
           : tramp([=]{ return forceGetAux(key, alternate, tail(xs)); }))
        : tramp(alternate);
    }

  public:
    //                  _          ___     _
    //  _ __  __ _ _  _| |__  ___ / __|___| |_
    // | '  \/ _` | || | '_ \/ -_) (_ / -_)  _|
    // |_|_|_\__,_|\_, |_.__/\___|\___\___|\__|
    //             |__/

    /**
     * @brief Return an optional value associated with an input key in
     * this `AList`.
     */
    optional<T>
    maybeGet(K key) const {
      return optional<T>(maybeGetAux(key, data));
    }

    /**
     * @brief Return an optional value associated with an input key in
     * the input `AList`.
     */
    friend optional<T>
    maybeGet(K key, AList xs){
      return optional<T>(maybeGetAux(key, xs.data));
    }

  private:

    static Trampoline<optional<T>>
    maybeGetAux(K key, data_type xs){
      using tramp = Trampoline<optional<T>>;
      return xs.hasData()
        ? (head(xs).first == key
           ? tramp(head(xs).second)
           : tramp([=]{ return maybeGetAux(key, tail(xs)); }))
        : tramp(optional<T>{nullopt});
    }


  public:

    //  _             ___     _
    // | |_ _ _ _  _ / __|___| |_
    // |  _| '_| || | (_ / -_)  _|
    //  \__|_|  \_, |\___\___|\__|
    //          |__/

    T
    tryGet(K key) const {
      return T(tryGetAux(key, data));
    }

    friend T
    tryGet(K key, AList xs){
      return T(tryGetAux(key, xs.data));
    }

  private:

    static Trampoline<T>
    tryGetAux(K key, data_type xs){
      using tramp = Trampoline<T>;
      return xs.hasData()
        ? (head(xs).first == key
           ? tramp(head(xs).second)
           : tramp([=]{ return tryGetAux(key, tail(xs)); }))
        : throw logic_error(
          "\n" __FILE__ ":" + std::to_string(__LINE__) + ":0 "
          "AList does not have requested key!\n");
    }


  private:

    AList(data_type input_data)
      : data(input_data)
    {}

    //  _            ___       _
    // | |_  __ _ __|   \ __ _| |_ __ _
    // | ' \/ _` (_-< |) / _` |  _/ _` |
    // |_||_\__,_/__/___/\__,_|\__\__,_|
  public:

    bool
    hasData() const { return Operators::hasData(data); }

    friend bool
    hasData(AList xs){ return xs.hasData(); }

    //  _    ___            _
    // (_)__| __|_ __  _ __| |_ _  _
    // | (_-< _|| '  \| '_ \  _| || |
    // |_/__/___|_|_|_| .__/\__|\_, |
    //                |_|       |__/
  public:

    bool
    isEmpty(){ return isNull(data); }

    friend bool
    isEmpty(AList xs){ return isNull(xs.data); }

  }; // end of class AList

  template<typename K, typename T>
  const AList<K,T> empty_alist{};

} // end of namespace ListProcessing::Dynamic::Details
