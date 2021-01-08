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

    /**
     * @brief Return true if the input queue is empty and
     * false if it has data.
     */
    friend bool
    isEmpty(Queue xs){
      return isNull(xs.output);
    }

    /**
     * @brief Return a list with the same elments as the queue.
     */
    friend data_type
    toList(Queue xs){
      return append(xs.output, reverse(xs.input));
    }

    /**
     * @brief Return true if the input queues have the same number
     * of values and all corresponding pair of elements are equal,
     * otherwise return false.
     */
    friend bool
    operator ==(Queue xs, Queue ys){
      return toList(xs) == toList(ys);
    }

    /**
     * @brief Return true if the input queues are not equal and
     * return false if they are equal.
     */
    friend bool
    operator !=(Queue xs, Queue ys){
      return !(xs == ys);
    }

    //   __             _
    //  / _|_ _ ___ _ _| |_
    // |  _| '_/ _ \ ' \  _|
    // |_| |_| \___/_||_\__|
  public:

    /**
     * @brief Return the value at the front of this queue
     */
    value_type
    front() const {
      return head(output);
    }

    /**
     * @brief Return the value at the front of the queue
     */
    friend value_type
    front(Queue xs){
      return xs.front();
    }

    //  _ __  ___ _ __
    // | '_ \/ _ \ '_ \.
    // | .__/\___/ .__/
    // |_|       |_|
  public:
    /**
     * @brief Remove the value at the front of this queue
     */
    Queue
    pop() const {
      return length(output) > 1
        ? Queue(input, tail(output))
        : Queue(nil<value_type>, reverse(input));
    }

    /**
     * @brief Remove the value at the front of the queue
     */
    friend Queue
    pop(Queue xs){
      return xs.pop();
    }

    //               _
    //  _ __ _  _ __| |_
    // | '_ \ || (_-< ' \.
    // | .__/\_,_/__/_||_|
    // |_|
  public:

    /**
     * @brief Push a value onto the back of the queue
     */
    Queue
    push(const_reference x) const {
      return output.hasData()
        ? Queue(cons(x, input), output)
        : Queue(nil<value_type>, reverse(cons(x, input)));
    }

    /**
     * @brief Push a value onto the back of the queue
     */
    friend Queue
    push(Queue xs, const_reference x){
      return xs.push(x);
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

  /**
   * @brief Insert the elements of a list into a queue.
   */
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
  class QueueConstructor : public Static_callable<QueueConstructor> {
  public:
    template<typename T, typename ... Ts>
    static constexpr auto
    call(T&& x, Ts&& ... xs){
      using U = common_type_t<decay_t<T>, decay_t<Ts> ...>;
      return listIntoQueue(list(forward<T>(x), forward<Ts>(xs) ...), empty_queue<U>);
    }
  } constexpr queue{};



} // end of namespace ListProcessing::Dynamic::Details
