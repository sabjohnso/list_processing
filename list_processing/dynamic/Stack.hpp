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

    //               _
    //  _ __ _  _ __| |_
    // | '_ \ || (_-< ' \.
    // | .__/\_,_/__/_||_|
    // |_|
  public:
    /**
     * @brief Return a stack equivalent to this stack
     * with the input value pushed onto it.
     */
    Stack
    push(const_reference x) const {
      return Stack(cons(x, data));
    }

    /**
     * @brief Return a stack equivalent to the input stack
     * with the input value pushed onto it.
     */
    friend Stack
    push(const_reference x, Stack xs)
    {
      return Stack(cons(x, xs.data));
    }


    //  _            ___       _
    // | |_  __ _ __|   \ __ _| |_ __ _
    // | ' \/ _` (_-< |) / _` |  _/ _` |
    // |_||_\__,_/__/___/\__,_|\__\__,_|
  public:
    /**
     * @brief Return true if this `Stack` has data and
     * false if it is emtpy.
     */
    bool
    hasData() const { return data.hasData(); }

    /**
     * @brief Return true if the input `Stack` has data and
     * false if it is emtpy.
     */
    friend bool
    hasData(Stack xs){ return xs.hasData(); }

    //  _    ___            _
    // (_)__| __|_ __  _ __| |_ _  _
    // | (_-< _|| '  \| '_ \  _| || |
    // |_/__/___|_|_|_| .__/\__|\_, |
    //                |_|       |__/
  public:
    /**
     * @brief Return true if this stack is empty and
     * false if it has data.
     */
    bool
    isEmpty() const { return ! hasData(); }

    /**
     * @brief Return true if the input stack is empty and
     * false if it has data.
     */
    friend bool
    isEmpty(Stack xs){ return xs.isEmpty(); }

    //  _
    // | |_ ___ _ __
    // |  _/ _ \ '_ \.
    //  \__\___/ .__/
    //         |_|
  public:
    /**
     * @brief Return the value at the top of this stack.
     *
     * @details Is is an error to call this function with an
     * empty stack and an exception will be thrown in that situation.
     */
    value_type
    top() const {
      return (! isEmpty())
        ? head(data)
        : throw logic_error("Cannot read top of empty stack");
    }

    /**
     * @brief Return the value at the top of the stack.
     *
     * @details Is is an error to call this function with an
     * empty stack and an exception will be thrown in that situation.
     */
    friend value_type
    top(Stack xs){ return xs.top(); }


    //  _ __  ___ _ __
    // | '_ \/ _ \ '_ \.
    // | .__/\___/ .__/
    // |_|       |_|
  public:
    /**
     * @brief Return a stack that is equivalent to this stack with the top
     * value removed.
     *
     * @brief This function accepts empty stacks as well as stack with data.  In the case
     * of empty stacks, an empty stack is returned
     */
    Stack
    pop() const { return Stack(tail(data)); }

    /**
     * @brief Return a stack that is equivalent to the input stack with the top
     * value removed.
     *
     * @brief This function accepts empty stacks as well as stack with data.  In the case
     * of empty stacks, an empty stack is returned
     */
    friend Stack
    pop(Stack xs){ return xs.stack(); }

    //     _
    //  __| |_ _ ___ _ __
    // / _` | '_/ _ \ '_ \.
    // \__,_|_| \___/ .__/
    //              |_|
  public:
    /**
     * @brief Same as pop
     */
    Stack
    drop() const { return pop(); }

    /**
     * @brief Same as pop
     */
    friend Stack
    drop(Stack xs){ return xs.pop(); }



    //     _              ___
    //  __| |_ _ ___ _ __|_  )
    // / _` | '_/ _ \ '_ \/ /
    // \__,_|_| \___/ .__/___|
    //              |_|
  public:
    /**
     * @brief Return a stack that is equivalent to the input stack
     * with its top two values removed
     */
    Stack
    drop2() const { return drop().drop(); }

    /**
     * @brief Return a stack that is equivalent to the input stack
     * with its top two values removed
     */
    friend Stack
    drop2(Stack xs)
    {
      return xs.drop2();
    }


    //     _              ____
    //  __| |_ _ ___ _ __|__ /
    // / _` | '_/ _ \ '_ \|_ \.
    // \__,_|_| \___/ .__/___/
    //              |_|
  public:
    /**
     * @brief Return a stack that is equivalent to this stack
     * with its top three values removed
     */
    Stack
    drop3() const { return drop2().drop(); }

    /**
     * @brief Return a stack that is equivalent to the input stack
     * with its top three values removed
     */
    friend Stack
    drop3(Stack xs)
    {
      return xs.drop3();
    }

    //     _
    //  __| |_  _ _ __
    // / _` | || | '_ \.
    // \__,_|\_,_| .__/
    //           |_|
  public:
    /**
     * @brief Return a stack that is equivalent to this stack with
     * its top value duplicated
     */
    Stack
    dup() const { return push(top()); }

    /**
     * @brief Return a stack that is equivalent to the input stack with
     * its top value duplicated
     */
    friend Stack
    dup(Stack xs)
    {
      return xs.dup();
    }



    //  ____ __ ____ _ _ __
    // (_-< V  V / _` | '_ \.
    // /__/\_/\_/\__,_| .__/
    //                |_|
  public:
    /**
     * @brief Return a stack that is equivalent to this stack with
     * the position of its top two elements swapped
     */
    Stack
    swap() const {
      return drop2()
        .push(top())
        .push(drop().top());
    }

    /**
     * @brief Return a stack that is equivalent to the input stack with
     * the position of its top two elements swap
     */
    friend Stack
    swap(Stack xs){ return xs.swap(); }


    //       _
    //  _ _ (_)_ __
    // | ' \| | '_ \.
    // |_||_|_| .__/
    //        |_|
  public:
    /**
     * @brief Return a stack that is equivalent to this stack
     * with its second value removed
     */
    Stack
    nip() const {
      return drop2().push(top());
    }

    /**
     * @brief Return a stack that is equivalent to the input stack
     * with its second value removed
     */
    friend Stack
    nip(Stack xs){ return xs.nip(); }

    //  _           _
    // | |_ _  _ __| |__
    // |  _| || / _| / /
    //  \__|\_,_\__|_\_\.
  public:
    /**
     * @brief Return a stack that is equivalent to this stack with
     * a copy of the top value inserted between the second and third values.
     */
    Stack
    tuck() const {
      return drop2()
        .push(top())
        .push(drop().top())
        .push(top());
    }

    /**
     * @brief Return a stack that is equivalent to the input stack with
     * a copy of the top value inserted between the second and third values.
     */
    friend Stack
    tuck(Stack xs)
    {
      return xs.tuck();
    }


    //  _____ _____ _ _
    // / _ \ V / -_) '_|
    // \___/\_/\___|_|
  public:
    /**
     * @brief Return a stack that is equivalent to the input stack with
     * a copy of the second value pused onto the top.
     */
    Stack
    over() const {
      return push(drop().top());
    }

    /**
     * @brief Return a stack that is equivalent to the input stack with
     * a copy of the second value pused onto the top.
     */
    friend Stack
    over(Stack xs){ return xs.over(); }


    //          _
    //  _ _ ___| |_
    // | '_/ _ \  _|
    // |_| \___/\__|
  public:
    /**
     * @brief Return a stack that is equivalent to this stack
     * with the top three values rotated.
     */
    Stack
    rot(Stack xs)
    {
      return drop3()
        .push(drop().top())
        .push(top())
        .push(drop2().top());
    }

    /**
     * @brief Return a stack that is equivalent to the input stack
     * with the top three values rotated.
     */
    friend Stack
    rot(Stack xs)
    {
      return xs.rot();
    }

    //                 _
    //  __ _ _ __ _ __/ |
    // / _` | '_ \ '_ \ |
    // \__,_| .__/ .__/_|
    //      |_|  |_|
  public:
    /**
     * @brief Return a stack that is equivalent to the input
     * stack with the top value transformed by the input function.
     */
    template<typename F>
    Stack
    app1(F f){
      return drop().push(f(top()));
    }

    /**
     * @brief Return a stack that is equivalent to the input
     * stack with the top value transformed by the input function.
     */
    template<typename F>
    friend Stack
    app1(Stack xs, F f){
      return xs.app1(f);
    }

    //                 ___
    //  __ _ _ __ _ __|_  )
    // / _` | '_ \ '_ \/ /
    // \__,_| .__/ .__/___|
    //      |_|  |_|
  public:
    /**
     * @brief Return a stack that is equivalent to this
     * stack with the top two values removed and the result
     * of applying the input function to those values added.
     */
    template<typename F>
    Stack
    app2(F f){
      return drop2().push(f(top(), drop().top()));
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
      return xs.app2(f);
    }


    ////////////////////////////////////////////////////////////////////////


    /**
     * @brief Return true if all corresponding pairs of values
     * are equal.
     */
    friend bool
    operator==(Stack xs, Stack ys)
    {
      return (xs.isEmpty() && ys.isEmpty())
        ? true
        : (((! xs.isEmpty()) && (! ys.isEmpty()))
           ? (xs.top() == ys.top()) && (xs.drop() == ys.drop())
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

  }; // end of class Stack

  template<typename T>
  const Stack<T> empty_stack{};

} // end of namespace ListProcessing::Dynamic::Details
