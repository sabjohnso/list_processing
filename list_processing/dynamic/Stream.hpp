#pragma once

//
// ... List Processing header files
//
#include <list_processing/dynamic/Nil.hpp>
#include <list_processing/dynamic/import.hpp>
#include <list_processing/dynamic/List.hpp>

namespace ListProcessing::Dynamic::Details {

  template<typename T>
  class Stream
  {
    using F = function<pair<T, Stream>()>;

  public:
    using value_type = T;
    using const_reference = value_type const&;

    Stream() = default;

    Stream(Nil)
      : Stream()
    {}

    template<typename U>
    Stream(U&& x, Stream const& xs)
      : ptr(make_shared<Kernel>(std::forward<U>(x), xs))
    {}

    template<typename U>
    Stream(U&& x, Nil)
      : ptr(make_shared<Kernel>(std::forward<U>(x), Stream{}))
    {}

    Stream(F f)
      : ptr(make_shared<Kernel>(f))
    {}

    //  _            ___       _
    // | |_  __ _ __|   \ __ _| |_ __ _
    // | ' \/ _` (_-< |) / _` |  _/ _` |
    // |_||_\__,_/__/___/\__,_|\__\__,_|

    /**
     * @brief Return true if this `Stream` has data and false
     * if it does not.
     */
    bool
    hasData() const
    {
      return bool(ptr);
    }

    /**
     * @brief Return true if the input `Stream` has data and false
     * if it does not.
     */
    friend bool
    hasData(Stream xs)
    {
      return xs.hasData();
    };

    //  _    ___            _
    // (_)__| __|_ __  _ __| |_ _  _
    // | (_-< _|| '  \| '_ \  _| || |
    // |_/__/___|_|_|_| .__/\__|\_, |
    //                |_|       |__/
    /**
     * @brief Return true if this `Stream` is empty and false
     * if it is not.
     */
    bool
    isEmpty() const
    {
      return !hasData();
    }

    /**
     * @brief Return true if the input `Stream` is empty and false
     * if it is not.
     */
    friend bool
    isEmpty(Stream xs)
    {
      return xs.isEmpty();
    }

    //  _                _
    // | |_  ___ __ _ __| |
    // | ' \/ -_) _` / _` |
    // |_||_\___\__,_\__,_|

    value_type
    head() const
    {
      return hasData()
               ? ptr->head()
               : throw logic_error("Cannot access the head of an empty Stream");
    }

    friend value_type
    head(Stream xs)
    {
      return xs.head();
    }

    //  _        _ _
    // | |_ __ _(_) |
    // |  _/ _` | | |
    //  \__\__,_|_|_|
    /**
     * @brief Return the tail of this stream
     */
    Stream
    tail() const
    {
      return hasData() ? ptr->tail() : *this;
    }

    /**
     * @brief Return the tail of the input stream
     */
    friend Stream
    tail(Stream xs)
    {
      return xs.tail();
    }

    //  __ ___ _ _  ___
    // / _/ _ \ ' \(_-<
    // \__\___/_||_/__/
    /**
     * @brief Return a stream with a value pushed onto the
     * front of this list.
     */
    Stream
    cons(const_reference x) const
    {
      return Stream(x, *this);
    }

    /**
     * @brief Return a stream with a value pushed onto the
     * front of the input list.
     */
    friend Stream
    cons(const_reference x, Stream xs)
    {
      return xs.cons(x);
    }

    //                              _
    //  __ _ _ __ _ __  ___ _ _  __| |
    // / _` | '_ \ '_ \/ -_) ' \/ _` |
    // \__,_| .__/ .__/\___|_||_\__,_|
    //      |_|  |_|
    /**
     * @brief Return this stream appended to the input
     * stream.
     */
    Stream
    append(Stream xs) const
    {
      return hasData() ? (xs.hasData() ? Stream([=, *this] {
        return pair(xs.head(), append(xs.tail()));
      })
                                       : *this)
                       : xs;
    }

    //
    //
    // toList
    //
    auto toList() const {
      return buildList([=,this](auto index){return listRef(index);}, this->length());
    }


    /**
     * @brief Return the second input stream appended to the
     * first input stream stream.
     */
    friend Stream
    append(Stream xs, Stream ys)
    {
      return ys.append(xs);
    }

    //  _ __  __ _ _ __
    // | '  \/ _` | '_ \.
    // |_|_|_\__,_| .__/
    //            |_|
    /**
     * @brief Return a Stream with the input function mapped over this
     * stream.
     */
    template<typename G, typename U = decay_t<result_of_t<G(T)>>>
    Stream<U>
    map(G g) const
    {
      return hasData() ? Stream<U>([=, xs = *this] {
        return pair(g(xs.head()), xs.tail().map(g));
      })
                       : Stream<U>();
    }

    template<typename G>
    friend auto
    map(G g, Stream xs)
    {
      return xs.map(g);
    }

    //  _               _   _
    // | |___ _ _  __ _| |_| |_
    // | / -_) ' \/ _` |  _| ' \.
    // |_\___|_||_\__, |\__|_||_|
    //            |___/

    /**
     * @brief Return the length of this stream.
     *
     * @details For an infinite stream, this function will not return
     */
    size_type
    length() const
    {
      using tramp = Trampoline<size_type>;
      struct Aux
      {
        tramp
        run(Stream xs, size_type accum) const
        {
          return xs.hasData()
                   ? tramp([=, *this] { return run(xs.tail(), accum + 1); })
                   : tramp(accum);
        }
      } constexpr aux{};
      return size_type(aux.run(*this, 0));
    }

    /**
     * @brief Return the length of the input stream.
     *
     * @details For an infinite stream, this function will not return
     */
    friend size_type
    length(Stream xs)
    {
      return xs.length();
    }

    //  _        _
    // | |_ __ _| |_____
    // |  _/ _` | / / -_)
    //  \__\__,_|_\_\___|
    Stream
    take(size_type n) const
    {
      return hasData() && n > 0
               ? Stream([=, *this] { return pair(head(), tail().take(n - 1)); })
               : Stream();
    }

    friend Stream
    take(size_type n, Stream xs)
    {
      return xs.take(n);
    }

    //     _
    //  __| |_ _ ___ _ __
    // / _` | '_/ _ \ '_ \.
    // \__,_|_| \___/ .__/
    //              |_|
    Stream
    drop(size_type n) const
    {
      return hasData() && n > 0 ? tail().drop(n - 1) : *this;
    }

    friend Stream
    drop(size_type n, Stream xs)
    {
      return xs.drop(n);
    }

    //     _                      ___      __
    //  __| |_ _ _ ___ __ _ _ __ | _ \___ / _|
    // (_-<  _| '_/ -_) _` | '  \|   / -_)  _|
    // /__/\__|_| \___\__,_|_|_|_|_|_\___|_|
    value_type
    streamRef(index_type i) const
    {
      using tramp = Trampoline<value_type>;
      struct Aux
      {
        tramp
        run(index_type i, Stream xs) const
        {
          return xs.hasData()
                   ? (i > 0
                        ? tramp([=, *this] { return run(i - 1, xs.tail()); })
                        : tramp(xs.head()))
                   : throw logic_error("no more data in stream to reference");
        }
      } constexpr aux{};
      return value_type(aux.run(i, *this));
    }

    friend value_type
    streamRef(index_type i, Stream xs)
    {
      return xs.streamRef(i);
    }

    //  _ _    _   ___      __
    // | (_)__| |_| _ \___ / _|
    // | | (_-<  _|   / -_)  _|
    // |_|_/__/\__|_|_\___|_|

    value_type
    listRef(index_type i) const
    {
      return streamRef(i);
    }

    friend value_type
    listRef(index_type i, Stream xs)
    {
      return xs.streamRef(i);
    }

    //     _     _    _    _
    //  __| |___| |  (_)__| |_
    // / _` / _ \ |__| (_-<  _|
    // \__,_\___/____|_/__/\__|

    template<typename F>
    F
    doList(F f) const
    {
      using tramp = Trampoline<F>;
      struct aux
      {
        tramp
        run(F f, Stream xs) const
        {
          return xs.hasData()
                   ? tramp([=, *this, x = xs.head(), xs = xs.tail()] {
                       f(x);
                       return run(f, xs);
                     })
                   : tramp(f);
        }
      } constexpr aux{};
      return F(aux.run(f, *this));
    }

    template<typename F>
    friend F
    doList(Stream xs, F f)
    {
      return xs.doList(f);
    }

    //   __     _    _ _
    //  / _|___| |__| | |
    // |  _/ _ \ / _` | |__
    // |_| \___/_\__,_|____|
    template<typename F, typename U>
    U
    foldL(F f, U init)
    {
      using tramp = Trampoline<U>;
      struct Aux
      {
        tramp
        run(F f, U init, Stream xs) const
        {
          return xs.hasData()
                   ? tramp([=,
                            *this,
                            init = std::move(init),
                            x = xs.head(),
                            xs = xs.tail()] { return run(f, f(init, x), xs); })
                   : tramp(init);
        }
      } constexpr aux{};
      return U(aux.run(f, init, *this));
    }

    template<typename F, typename U>
    friend U
    foldL(F f, U init, Stream xs)
    {
      return xs.foldL(f, init);
    }

  private:
    class Kernel
    {
      using Pair = pair<value_type, Stream>;
      using Data = variant<Pair, F>;

    public:
      Kernel(Kernel&& input)
        : data(move(input.data))
      {}

      template<typename U>
      Kernel(U&& x, Stream const& xs)
        : data(pair(std::forward<U>(x), xs))
      {}

      Kernel(F f)
        : data(f)
      {}

    public:
      value_type
      head() const
      {
        reify();
        return get<Pair>(data).first;
      }

      Stream
      tail() const
      {
        reify();
        return get<Pair>(data).second;
      }

    private:
      void
      reify() const
      {
        if (holds_alternative<F>(data)) {
          lock_guard lock{mex};
          if (holds_alternative<F>(data)) {
            data = get<F>(data)();
          }
        }
      }

      mutable Data data;
      mutable mutex mex;
    };

    using KernelPointer = shared_ptr<const Kernel>;
    KernelPointer ptr;

  }; // end of class Stream;

  template<typename T, typename U>
  Stream(T&&, Stream<U>) -> Stream<U>;

  template<typename T>
  Stream(T&&, Nil) -> Stream<decay_t<T>>;

  template<typename T>
  Stream(function<pair<T, Stream<T>>()> f) -> Stream<T>;

  template<typename T>
  inline const Stream<T> empty_stream{};

  template<typename T>
  class StreamOf : public Static_callable<StreamOf<T>>
  {
  public:
    static Stream<T>
    call()
    {
      return empty_stream<T>;
    }

    template<typename U, typename... Us>
    static Stream<T>
    call(U&& x, Us&&... xs)
    {
      return Stream<T>(std::forward<U>(x), call(std::forward<Us>(xs)...));
    }
  };

  template<typename T>
  constexpr StreamOf<T> streamOf{};

  class StreamConstructor : public Static_callable<StreamConstructor>
  {
  public:
    template<typename T, typename... Ts>
    static auto
    stream(T&& x, Ts&&... xs)
    {
      using U = common_type_t<decay_t<T>, decay_t<Ts>...>;
      return streamOf<U>(std::forward<T>(x), std::forward<Ts>(xs)...);
    }
  } constexpr stream{};

  class BuildStream : public Static_curried<BuildStream, Nat<2>>
  {
  public:
    template<typename F, typename U = decay_t<result_of_t<F(index_type)>>>
    static Stream<U>
    call(size_type n, F&& f)
    {
      return aux(n, f, 0);
    }

  private:
    template<typename F, typename U = decay_t<result_of_t<F(index_type)>>>
    static Stream<U>
    aux(size_type n, F&& f, index_type i)
    {
      return i < n ? Stream<U>([=] {
        return pair<U, Stream<U>>(f(i), aux(n, f, i + 1));
      })
                   : empty_stream<U>;
    }

  } constexpr buildStream{};

  class Iterate : public Static_curried<Iterate, Nat<2>>
  {
  public:
    template<typename T, typename F, typename U = decay_t<T>>
    static Stream<U>
    call(T x, F f)
    {
      return Stream<U>([=] { return pair(x, call(f(x), f)); });
    }
  } constexpr iterate{};

} // end of namespace ListProcessing::Dynamic::Details
