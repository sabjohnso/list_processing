#pragma once

//
// ... List Processing header files
//
#include <list_processing/dynamic/import.hpp>
#include <list_processing/dynamic/List.hpp>


namespace ListProcessing::Dynamic::Details
{

  /**
   * @brief A class template describing homogeneous dynamic queues.
   */
  template<typename T>
  class Queue
  {
  public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = value_type const&;

    Queue()
      : input(nil<value_type>)
      , output(nil<value_type>)
    {}
  private:

    using data_type = List<value_type>;

    Queue(data_type input, data_type output)
      : input(input)
      , output(output)
    {}

    data_type input;
    data_type output;

    friend bool
    isEmpty(Queue xs){
      return isNull(xs.output);
    }

    friend data_type
    toList(Queue xs){
      return append(xs.output, reverse(xs.input));
    }

    friend bool
    operator ==(Queue xs, Queue ys){
      return toList(xs) == toList(ys);
    }

    friend bool
    operator !=(Queue xs, Queue ys){
      return !(xs == ys);
    }

    /**
     * @brief Return the value at the front of the queue
     */
    friend value_type
    front(Queue xs){
      return head(xs.output);
    }

    /**
     * @brief Remove the value at the front of the queue
     */
    friend Queue
    pop(Queue xs){
      return length(xs.output) > 1
        ? Queue(xs.input, tail(xs.output))
        : Queue(nil<value_type>, reverse(xs.input));
    }

    /**
     * @brief Push a value onto the back of the queue
     */
    friend Queue
    push(Queue xs, const_reference x){
      return hasData(xs.output)
        ? Queue(cons(x, xs.input), xs.output)
        : Queue(nil<value_type>, reverse(cons(x, xs.input)));
    }

    /**
     * @brief Display a queue in an output stream
     */
    template<typename Stream>
    friend Stream&
    operator<<(Stream& os, Queue const& xs)
    {
      return isEmpty(xs)
        ?  os << "#Queue()"
        :  os << "#Queue(" << front(xs) << ", ...)";
    }

    /**
     * @brief Display a queue in an output stream
     */

    friend ostream&
    operator<<(ostream& os, Queue const& xs)
    {
      return isEmpty(xs)
        ?  os << "#Queue()"
        :  os << "#Queue(" << front(xs) << ", ...)";
    }

  }; // end of class Queue

  template<typename T>
  inline const Queue<T> empty_queue{};


  template<typename T>
  Queue<T>
  listIntoQueue(List<T> xs, Queue<T> ys){
    return hasData(xs)
      ? listIntoQueue(tail(xs), push(ys, head(xs)))
      : ys;
  }


  /**
   * @brief Return a queue containing the input arguments,
   * where the left-most argument is the first value.
   *
   * front(queue(1, 2, 3))
   *   => 1
   */
  template<
    typename T1, typename T2, typename ... Ts,
    typename T = common_type_t<T1, T2, Ts ...>>
  Queue<T>
  queue(T1 const& x1, T2 const& x2, Ts const& ... xs){
    return listIntoQueue(list(x1, x2, xs ...), empty_queue<T>);
  }

} // end of namespace ListProcessing::Dynamic::Details
