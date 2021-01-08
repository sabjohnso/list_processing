#pragma once

//
// ... List Processing header files
//
#include <list_processing/dynamic/List.hpp>
#include <list_processing/dynamic/import.hpp>

namespace ListProcessing::Dynamic::Details
{
  /**
   * @brief A bi-directional sequence of values
   */
  template<typename T>
  class Tape
  {
  public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = value_type const&;

    Tape()
      : data(nil<value_type>)
      , context(nil<value_type>)
    {}

  private:
    using data_type = List<value_type>;

    Tape(data_type input_data, data_type input_context)
      : data(input_data)
      , context(input_context)
    {}

    data_type data;
    data_type context;

    /**
     * @brief Return true if the elements of the tapes are
     * equal and the tapes are at the same position
     */
    friend bool
    operator==(Tape xs, Tape ys)
    {
      return xs.data == ys.data && xs.context == ys.context;
    }

    /**
     * @brief Return true if the input tapes are not equal
     */
    friend bool
    operator!=(Tape xs, Tape ys)
    {
      return !(xs == ys);
    }


    //  _ _ _____ _____ _ _ ___ ___
    // | '_/ -_) V / -_) '_(_-</ -_)
    // |_| \___|\_/\___|_| /__/\___|
  public:

    /**
     * @brief Reverse the elements of this tape
     */
    Tape
    reverse() const { return Tape(context, data); }

    /**
     * @brief Reverse the elements of the input tape
     */
    friend Tape
    reverse(Tape xs){ return xs.reverse(); }

    //  _      _  _   ___          _
    // (_)___ /_\| |_| _ ) __ _ __| |__
    // | (_-</ _ \  _| _ \/ _` / _| / /
    // |_/__/_/ \_\__|___/\__,_\__|_\_\.
  public:

    /**
     * @brief Return true if this tape is at the back
     */
    bool
    isAtBack() const { return data.isEmpty(); }

    /**
     * @brief Return true if the tape is at the back
     */
    friend bool
    isAtBack(Tape xs)
    {
      return xs.isAtBack();
    }

    //  _      _  _   ___            _
    // (_)___ /_\| |_| __| _ ___ _ _| |_
    // | (_-</ _ \  _| _| '_/ _ \ ' \  _|
    // |_/__/_/ \_\__|_||_| \___/_||_\__|
  public:

    /**
     * @brief Return true if this tape is at the front
     */
    bool
    isAtFront() const
    {
      return context.isNull();
    }

    /**
     * @brief Return true if the tape is at the front
     */
    friend bool
    isAtFront(Tape xs)
    {
      return isNull(xs.context);
    }

    //  _    ___            _
    // (_)__| __|_ __  _ __| |_ _  _
    // | (_-< _|| '  \| '_ \  _| || |
    // |_/__/___|_|_|_| .__/\__|\_, |
    //                |_|       |__/
  public:

    /**
     * @brief Return true if this tape is empty
     */
    bool
    isEmpty() const
    {
      return isAtFront() && isAtBack();
    }

    /**
     * @brief Return true if the tape is empty
     */
    friend bool
    isEmpty(Tape xs)
    {
      return xs.isAtFront() && xs.isAtBack();
    }


    //  _                  _
    // (_)_ _  ___ ___ _ _| |_
    // | | ' \(_-</ -_) '_|  _|
    // |_|_||_/__/\___|_|  \__|
  public:

    /**
     * @brief Insert a value into this tape
     */
    Tape
    insert(const_reference x) const
    {
      return Tape( cons(x, data), context);
    }

    /**
     * @brief Insert a value into the tape
     */
    friend Tape
    insert(const_reference x, Tape xs)
    {
      return xs.insert(x);
    }


    //  _ _ ___ _ __  _____ _____
    // | '_/ -_) '  \/ _ \ V / -_)
    // |_| \___|_|_|_\___/\_/\___|
  public:

    /**
     * @brief Remove a value from this tape
     */
    Tape
    remove() const
    {
      return Tape(tail(data), context);
    }

    /**
     * @brief Remove a value from the tape
     */
    friend Tape
    remove(Tape xs)
    {
      return xs.remove();
    }

    //             _ _
    // __ __ ___ _(_) |_ ___
    // \ V  V / '_| |  _/ -_)
    //  \_/\_/|_| |_|\__\___|
  public:

    Tape
    write(const_reference x)
    {
      return remove().insert(x);
    }
    /**
     * @brief Write the input value to the tape head
     */
    friend Tape
    write(Tape xs, const_reference x)
    {
      return xs.write(x);
    }

    //                  _
    //  _ _ ___ __ _ __| |
    // | '_/ -_) _` / _` |
    // |_| \___\__,_\__,_|
  public:

    /**
     * @brief Read the value from the head of this tape
     */
    const_reference
    read() const
    {
      return data.getHead();
    }

    /**
     * @brief Read the value from the head of the tape
     */
    friend value_type
    read(Tape xs)
    {
      return xs.read();
    }

    //               _ _   _
    //  _ __  ___ __(_) |_(_)___ _ _
    // | '_ \/ _ (_-< |  _| / _ \ ' \.
    // | .__/\___/__/_|\__|_\___/_||_|
    // |_|
  public:

    /**
     * @brief Return the position of this tape
     */
    index_type
    position() const { return context.length(); }

    /**
     * @brief Return the position of the tape
     */
    friend index_type
    position(Tape xs)
    {
      return xs.position();
    }


    //                     _      _
    //  _ _ ___ _ __  __ _(_)_ _ (_)_ _  __ _
    // | '_/ -_) '  \/ _` | | ' \| | ' \/ _` |
    // |_| \___|_|_|_\__,_|_|_||_|_|_||_\__, |
    //                                  |___/

    /**
     * @brief Return the number of items remaining in the tape
     */
    size_type
    remaining() const { return data.length(); }

    /**
     * @brief Return the number of items remaining in the tape
     */
    friend size_type
    remaining(Tape xs)
    {
      return xs.remaining();
    }


    //  _               _   _
    // | |___ _ _  __ _| |_| |_
    // | / -_) ' \/ _` |  _| ' \.
    // |_\___|_||_\__, |\__|_||_|
    //            |___/
    /**
     * @brief Return the total number of items in this tape
     */
    size_type
    length() const { return position() + remaining(); }

    /**
     * @brief Return the total number of items in the tape
     */
    friend size_type
    length(Tape xs)
    {
      return xs.position() +  xs.remaining();
    }

    //   __           _
    //  / _|_ __ ____| |
    // |  _\ V  V / _` |
    // |_|  \_/\_/\__,_|
    /**
     * @brief Move the the next item in this tape
     */
    Tape
    fwd() const { return Tape(tail(data), cons(head(data), context)); }

    /**
     * @brief Move the the next item in the tape
     */
    friend Tape
    fwd(Tape xs)
    {
      return xs.fwd();
    }

    //  _              _
    // | |____ __ ____| |
    // | '_ \ V  V / _` |
    // |_.__/\_/\_/\__,_|
    /**
     * @brief Move to the previous item in this tape
     */
  public:
    Tape
    bwd() const { return Tape(cons(head(context), data), tail(context)); }

    /**
     * @brief Move to the previous item in the tape
     */
    friend Tape
    bwd(Tape xs)
    {
      return xs.bwd();
    }

    //                    ___
    //  _ __  _____ _____| _ )_  _
    // | '  \/ _ \ V / -_) _ \ || |
    // |_|_|_\___/\_/\___|___/\_, |
    //                        |__/
  public:

    /**
     * @brief Move by the specified number of items
     */
    Tape
    moveBy(offset_type offset) const
    {
      return (offset > 0)
        ? fwd().moveBy(offset - 1)
        : (offset < 0 ? bwd().moveBy( offset + 1)
           : *this);
    }

    /**
     * @brief Move by the specified number of items
     */
    friend Tape
    moveBy(offset_type offset, Tape xs)
    {
      return xs.moveBy(offset);
    }


    //                   _____
    //  _ __  _____ ____|_   _|__
    // | '  \/ _ \ V / -_)| |/ _ \.
    // |_|_|_\___/\_/\___||_|\___/
    /**
     * @brief Move to the indicated position
     */
    Tape
    moveTo(index_type index)
    {
      return moveBy(index - position());
    }

    /**
     * @brief Move to the indicated position
     */
    friend Tape
    moveTo(index_type index, Tape xs)
    {
      return xs.moveTo(index);
    }

    //  _       ___            _
    // | |_ ___| __| _ ___ _ _| |_
    // |  _/ _ \ _| '_/ _ \ ' \  _|
    //  \__\___/_||_| \___/_||_\__|
  public:

    /**
     * @brief Move to the front of this tape
     */
    Tape
    toFront() const
    {
      return Tape(rappend(context, data), nil<value_type>);
    }

    /**
     * @brief Move to the front of the tape
     */
    friend Tape
    toFront(Tape xs)
    {
      return Tape(rappend(xs.context, xs.data), nil<value_type>);
    }

    //  _       ___          _
    // | |_ ___| _ ) __ _ __| |__
    // |  _/ _ \ _ \/ _` / _| / /
    //  \__\___/___/\__,_\__|_\_\.
  public:

    /**
     * @brief Move to the back of this tape
     */
    Tape
    toBack() const
    {
      return Tape(nil<value_type>, rappend(data, context));
    }

    /**
     * @brief Move to the back of the tape
     */
    friend Tape
    toBack(Tape xs)
    {
      return Tape(nil<value_type>, rappend(xs.data, xs.context));
    }

    //          _ _
    //  ____ __| (_)__ ___
    // (_-< '_ \ | / _/ -_)
    // /__/ .__/_|_\__\___|
    //    |_|
  public:

    /**
     * @brief Splice another tape into this tape
     */
    Tape
    splice(Tape ys){
      return Tape(append(data, ys.data), append(context, ys.context));
    }

    /**
     * @brief Splice another two tapes
     */
    friend Tape
    splice(Tape xs, Tape ys){
      return xs.splice(ys);
    }

    //  _       _    _    _
    // | |_ ___| |  (_)__| |_
    // |  _/ _ \ |__| (_-<  _|
    //  \__\___/____|_/__/\__|
  public:

    /**
     * @brief Return the remaining elemenets of the tape as a list
     */
    List<T>
    toList() const {
      return data;
    }

    /**
     * @brief Return the remaining elemenets of the tape as a list
     */
    friend List<T>
    toList(Tape xs){ return xs.toList(); }

  }; // end of class Tape

  template<typename T>
  const Tape<T> empty_tape{};

  template<typename T>
  Tape<T>
  tapeOf()
  {
    return empty_tape<T>;
  }

  template<typename T, typename T1, typename... Ts>
  Tape<T>
  tapeOf(T1 const& x, Ts const&... xs)
  {
    return insert(x, tapeOf<T>(xs...));
  }

  /**
   * @brief Construct a tape from a single input value
   */
  template<typename T>
  Tape<T>
  tape(T const& x)
  {
    return tapeOf<T>(x);
  }

  /**
   * @brief Construct a tape from the input values
   */
  template<
    typename T1,
    typename T2,
    typename... Ts,
    typename T = common_type_t<T1, T2, Ts...>>
  Tape<T>
  tape(T1 const& x1, T2 const& x2, Ts const&... xs)
  {
    return tapeOf<T>(x1, x2, xs...);
  }

} // end of namespace ListProcessing::Dynamic::Details
