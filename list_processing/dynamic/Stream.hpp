#pragma once

//
// ... List Processing header files
//
#include <list_processing/dynamic/List.hpp>
#include <list_processing/dynamic/Nil.hpp>
#include <list_processing/dynamic/Value.hpp>
#include <list_processing/dynamic/import.hpp>

namespace ListProcessing::Dynamic::Details {

  template<typename T>
  class Stream {
    using Head = Shared<T>;
    using Thunk = function<Stream()>;

  public:
    Stream()
      : pkernel_{make_shared<Kernel>()} {}

    template<convertible_to<Thunk> F>
    explicit Stream(F&& thunk)
      : pkernel_{make_shared<Kernel>(thunk)} {}

    Stream(const T& head, Stream tail)
      : pkernel_{make_shared<Kernel>(Head{head}, tail)} {}

    Stream(const T& head, Nil)
      : pkernel_{make_shared<Kernel>(Head{head}, Stream{})} {}

    Stream(Head head, Stream tail)
      : pkernel_{make_shared<Kernel>(head, tail)} {}

    bool
    hasData() const {
      assert(bool(pkernel_) && "pkernel_ should never be null");
      return pkernel_->hasData();
    }

    friend bool
    hasData(Stream xs) {
      return xs.hasData();
    }

    bool
    isEmpty() const {
      return !hasData();
    }

    friend bool
    isEmpty(Stream xs) {
      return xs.isEmpty();
    }

    size_type
    length() const {
      size_type count = 0;
      unique_ptr<Stream> ptr = std::make_unique<Stream>(*this);
      while (ptr->hasData()) {
        ptr = std::make_unique<Stream>(ptr->tail());
        ++count;
      }
      return count;
    }

    friend size_type
    length(Stream xs) {
      return xs.length();
    }

    Head
    head() const {
      return pkernel_->head();
    }

    friend Head
    head(Stream xs) {
      return xs.head();
    }

    Stream
    tail() const {
      return pkernel_->tail();
    }

    Head
    streamRef(size_type index) const {
      unique_ptr<Stream> ptr = std::make_unique<Stream>(*this);
      while (index > 0) {
        ptr = make_unique<Stream>(ptr->tail());
        --index;
      }
      return ptr->head();
    }

    friend Head
    streamRef(size_type index, Stream xs) {
      return xs.streamRef(index);
    }

    Head
    operator[](size_type index) const {
      return streamRef(index);
    }

    template<typename F>
    auto
    map(F f) const {
      using U = remove_cvref_t<invoke_result_t<F, T>>;
      auto recur = [f](auto recur, Stream xs) -> Stream<U> {
        return Stream<U>{[=] {
          return xs.hasData() ? Stream<U>{f(xs.head()), recur(recur, xs.tail())}
                              : Stream<U>{};
        }};
      };
      return recur(recur, *this);
    }

    template<typename F>
    friend auto
    map(F f, Stream xs) {
      return xs.map(f);
    }

    Stream
    take(size_type n) {
      if (n > 0) {
        auto recur = [n](auto recur, Stream xs, size_type index) -> Stream {
          return index < n && xs.hasData()
                   ? Stream{xs.head(), Stream{[=] {
                              return recur(recur, xs.tail(), index + 1);
                            }}}
                   : Stream{};
        };
        return recur(recur, *this, 0);
      } else if (n == 0) {
        return Stream{};
      } else {
        throw logic_error{"Cannot take a negative number of elements"};
      }
    }

    friend Stream
    take(size_type n, Stream xs) {
      return xs.take(n);
    }

    Stream
    cons(Head new_head) const {
      return Stream{new_head, *this};
    }

    friend Stream
    cons(Head new_head, Stream tail) {
      return tail.cons(new_head);
    }

    template<typename F, typename U>
    auto
    foldL(F f, U init) const {
      unique_ptr<Stream> ptr = make_unique<Stream>(*this);
      while (ptr->hasData()) {
        init = f(init, *ptr->head());
        ptr = make_unique<Stream>(ptr->tail());
      }
      return init;
    }

    template<typename F, typename U>
    friend auto
    foldL(F f, U init, Stream xs) {
      return xs.foldL(f, init);
    }

    friend Stream
    append(Stream xs, Stream ys) {
      auto recur = [ys](auto recur, Stream xs) -> Stream {
        return xs.hasData() ? Stream{xs.head(), Stream{[=] {
                                       return recur(recur, xs.tail());
                                     }}}
                            : ys;
      };
      return recur(recur, xs);
    }

    auto
    toList() const {
      unique_ptr<Stream> pstream = make_unique<Stream>(*this);
      unique_ptr<List<T>> plist = make_unique<List<T>>();
      while (pstream->hasData()) {
        plist = make_unique<List<T>>(listCons(*(pstream->head()), *plist));
        pstream = make_unique<Stream>(pstream->tail());
      }
      return reverse(*plist);
    }

    void
    pull() const {
      std::unique_ptr<Stream> ptr = make_unique<Stream>(*this);
      while (ptr->hasData()) {
        ptr = make_unique<Stream>(ptr->tail());
      }
    }

  private:
    struct Cell {
      Head head_;
      Stream tail_;

      Cell(Head head, Stream tail)
        : head_{head}
        , tail_{tail} {}

      Head
      head() const {
        return head_;
      }

      Stream
      tail() const {
        return tail_;
      }
    };

    class Kernel {

      using data_type = variant<Cell, Thunk>;
      using data_pointer = unique_ptr<data_type>;
      using mutex_pointer = unique_ptr<mutex>;

      mutable data_pointer pdata_{nullptr};
      mutable mutex_pointer pmex_{nullptr};

    public:
      Kernel() = default;
      Kernel(Kernel&& input)
        : pdata_{std::move(input.pdata_)}
        , pmex_{std::move(input.pmex_)} {}

      // This constructor does not need a mutex because
      // the data is already reified
      Kernel(Head head, Stream tail)
        : pdata_{std::make_unique<data_type>(Cell{head, tail})} {}

      Kernel(Thunk thunk)
        : pdata_{std::make_unique<data_type>(thunk)}
        , pmex_{std::make_unique<mutex>()} {}

      // A custom destructor is necessar to prevent a stack overflow when a
      // long stream is deleted.
      ~Kernel() {
        if ((!lazy()) && hasData()) {
          if (get<Cell>(*pdata_).tail_.pkernel_.unique()) {
            shared_ptr<const Kernel> pkernel =
              get<Cell>(*pdata_).tail_.pkernel_;
            get<Cell>(*pdata_).tail_.pkernel_.reset();
            while (!pkernel->lazy() && pkernel->hasData() &&
                   get<Cell>(*(pkernel->pdata_)).tail_.pkernel_.unique()) {
              shared_ptr<const Kernel> tmp = pkernel;
              pkernel = get<Cell>(*(pkernel->pdata_)).tail_.pkernel_;
              tmp.reset();
            }
          }
        }
      }

      bool
      lazy() const {
        return bool(pdata_) && holds_alternative<Thunk>(*pdata_);
      }

      bool
      hasData() const {
        reify();
        return bool(pdata_);
      }

      bool
      isEmpty() const {
        return !hasData();
      }

      Head
      head() const {
        return hasData() ? get<Cell>(*pdata_).head()
                         : throw logic_error(
                             "Cannot return the head of an empty stream");
      }

      Stream
      tail() const {
        return hasData() ? get<Cell>(*pdata_).tail() : Stream{};
      }

    private:
      void
      reify() const {
        if (lazy()) {
          assert(pmex_);
          lock_guard lock{*pmex_};
          while (lazy()) {
            Stream xs = get<Thunk>(*pdata_)();
            pdata_ = std::move(xs.pkernel_->pdata_);
          }
        }
      }
    };

    using kernel_pointer = shared_ptr<const Kernel>;
    kernel_pointer pkernel_{nullptr};
  };

  template<typename T>
  const Stream<T> empty_stream{};

  constexpr auto streamIterate = []<typename T, typename F>(const T& x, F f) {
    auto recur = [f](auto recur, const auto& x) -> Stream<T> {
      return Stream<T>{x, Stream<T>{[=] { return recur(recur, f(x)); }}};
    };
    return recur(recur, x);
  };

  constexpr auto buildStream = []<invocable<size_type> F>(size_type n, F f) {
    using T = std::remove_cvref_t<std::invoke_result_t<F, size_type>>;
    auto recur = [f, n](auto recur, size_type index) -> Stream<T> {
      return index < n ? Stream<T>{f(index), Stream<T>{[=] {
                                     return recur(recur, index + 1);
                                   }}}
                       : Stream<T>{};
    };
    return recur(recur, 0);
  };

} // end of namespace ListProcessing::Dynamic::Details
