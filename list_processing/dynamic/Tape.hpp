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

    /**
     * @brief Return true if the tape is at the back
     */
    friend bool
    isAtBack(Tape xs)
    {
      return isNull(xs.data);
    }

    /**
     * @brief Return true if the tape is at the front
     */
    friend bool
    isAtFront(Tape xs)
    {
      return isNull(xs.context);
    }

    /**
     * @brief Return true if the tape is empty
     */
    friend bool
    isEmpty(Tape xs)
    {
      return isAtFront(xs) && isAtBack(xs);
    }

    /**
     * @brief Insert a value into the tape
     */
    friend Tape
    insert(Tape xs, const_reference x)
    {
      return Tape(cons(x, xs.data), xs.context);
    }

    /**
     * @brief Remove a value from the tape
     */
    friend Tape
    remove(Tape xs)
    {
      return Tape(tail(xs.data), xs.context);
    }

    /**
     * @brief Write the input value to the tape head
     */
    friend Tape
    write(Tape xs, const_reference x)
    {
      return insert(remove(xs), x);
    }

    /**
     * @brief Read the value from the head of the tape
     */
    friend value_type
    read(Tape xs)
    {
      return head(xs.data);
    }

    /**
     * @brief Return the position of the tape
     */
    friend index_type
    position(Tape xs)
    {
      return length(xs.context);
    }

    /**
     * @brief Return the number of items remaining in the tape
     */
    friend size_type
    remaining(Tape xs)
    {
      return length(xs.data);
    }

    /**
     * @brief Return the total number of items in the tape
     */
    friend size_type
    length(Tape xs)
    {
      return position(xs) + remaining(xs);
    }

    /**
     * @brief Move the the next item in the tape
     */
    friend Tape
    fwd(Tape xs)
    {
      return Tape(tail(xs.data), cons(head(xs.data), xs.context));
    }

    /**
     * @brief Move to the previous item in the tape
     */
    friend Tape
    bwd(Tape xs)
    {
      return Tape(cons(head(xs.context), xs.data), tail(xs.context));
    }

    /**
     * @brief Move by the specified number of items
     */
    friend Tape
    moveBy(Tape xs, offset_type offset)
    {
      return (offset > 0)
               ? moveBy(fwd(xs), offset - 1)
               : ((offset < 0) ? moveBy(bwd(xs), offset + 1) : xs);
    }

    /**
     * @brief Move to the indicated position
     */
    friend Tape
    moveTo(Tape xs, index_type index)
    {
      return moveBy(xs, index - position(xs));
    }

    /**
     * @brief Move to the front of the tape
     */
    friend Tape
    toFront(Tape xs)
    {
      return Tape(rappend(xs.context, xs.data), nil<value_type>);
    }

    /**
     * @brief Move to the back of the tape
     */
    friend Tape
    toBack(Tape xs)
    {
      return Tape(nil<value_type>, rappend(xs.data, xs.context));
    }

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
    return insert(tapeOf<T>(xs...), x);
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
