#pragma once

//
// ... List Processing header files
//
#include <list_processing/dynamic/List.hpp>
#include <list_processing/dynamic/piping.hpp>

namespace ListProcessing::Dynamic::Details
{

  /**
   * @brief A stack
   */
  template<typename T>
  class Stack
  {

  public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = value_type const&;

    Stack()
      : data(nil<value_type>)
    {}

  private:
    using data_type = List<value_type>;

    Stack(data_type xs)
      : data(xs)
    {}

    data_type data;

    /**
     * @brief Return a stack equivalent to the input stack
     * with the input value pushed onto it.
     */
    friend Stack
    push(Stack xs, const_reference x)
    {
      return Stack(cons(x, xs.data));
    }

    /**
     * @brief Return true if the input stack is empty and
     * false if it has data.
     */
    friend bool
    isempty(Stack xs)
    {
      return isNull(xs.data);
    }

    /**
     * @brief Return the value at the top of the stack.
     *
     * @details Is is an error to call this function with an
     * empty stack and an exception will be thrown in that situation.
     */
    friend value_type
    top(Stack xs)
    {
      return (!isempty(xs)) ? head(xs.data) : throw logic_error("Cannot read top of empty stack");
    }

    /**
     * @brief Return a stack that is equivalent to the input stack with the top
     * value removed.
     *
     * @brief This function accepts empty stacks as well as stack with data.  In the case
     * of empty stacks, an empty stack is returned
     */
    friend Stack
    pop(Stack xs)
    {
      return Stack(tail(xs.data));
    }

    /**
     * @brief Same as pop
     */
    friend Stack
    drop(Stack xs)
    {
      return pop(xs);
    }

    /**
     * @brief Return a stack that is equivalent to the input stack
     * with its top two values removed
     */
    friend Stack
    drop2(Stack xs)
    {
      return drop(drop(xs));
    }

    /**
     * @brief Return a stack that is equivalent to the input stack
     * with its top three values removed
     */
    friend Stack
    drop3(Stack xs)
    {
      return drop(drop2(xs));
    }

    /**
     * @brief Return a stack that is equivalent to the input stack with
     * its top value duplicated
     */
    friend Stack
    dup(Stack xs)
    {
      return push(xs, top(xs));
    }

    /**
     * @brief Return a stack that is equivalent to the input stack with
     * the position of its top two elements swap
     */
    friend Stack
    swap(Stack xs)
    {
      return pipe(
        drop2(xs),
        [&](auto ys) { return push(ys, top(xs)); },
        [&](auto ys) { return push(ys, top(drop(xs))); });
    }

    /**
     * @brief Return a stack that is equivalent to the input stack
     * with its second value removed
     */
    friend Stack
    nip(Stack xs)
    {
      return push(drop2(xs), top(xs));
    }

    /**
     * @brief Return a stack that is equivalent to the input stack with
     * a copy of the top value inserted between the second and third values.
     */
    friend Stack
    tuck(Stack xs)
    {
      return pipe(
        drop2(xs),
        [&](auto ys) { return push(ys, top(xs)); },
        [&](auto ys) { return push(ys, top(drop(xs))); },
        [&](auto ys) { return push(ys, top(xs)); });
    }

    /**
     * @brief Return a stack that is equivalent to the input stack with
     * a copy of the second value pused onto the top.
     */
    friend Stack
    over(Stack xs)
    {
      return push(xs, top(drop(xs)));
    }

    /**
     * @brief Return a stack that is equivalent to the input stack
     * with the top three values rotated.
     */
    friend Stack
    rot(Stack xs)
    {
      return pipe(
        drop3(xs),
        [&](auto ys) { return push(ys, top(drop(xs))); },
        [&](auto ys) { return push(ys, top(xs)); },
        [&](auto ys) { return push(ys, top(drop2(xs))); });
    }

    /**
     * @brief Return true if all corresponding pairs of values
     * are equal.
     */
    friend bool
    operator==(Stack xs, Stack ys)
    {
      return (isempty(xs) && isempty(ys))
        ? true
        : (((!isempty(xs)) && (!isempty(ys)))
           ? (top(xs) == top(ys)) && (drop(xs) == drop(ys))
           : false);
    }

    /**
     * @brief Return true if the input stacks do not compare equal
     */
    friend bool
    operator!=(Stack xs, Stack ys)
    {
      return !(xs == ys);
    }

    /**
     * @brief Return a stack that is equivalent to the input
     * stack with the top value transformed by the input function.
     */
    template<typename F>
    friend Stack
    app1(Stack xs, F f)
    {
      return push(drop(xs), f(top(xs)));
    }

    /**
     * @brief Return a stack that is equivalent to the input
     * stack with the top two values removed and the result
     * of applying the input function to those values added.
     */
    template<typename F>
    friend Stack
    app2(Stack xs, F f)
    {
      return push(drop2(xs), f(top(xs), top(drop(xs))));
    }

  }; // end of class Stack

  template<typename T>
  const Stack<T> empty_stack{};

} // end of namespace ListProcessing::Dynamic::Details
