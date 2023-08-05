#pragma once

//
// ... Lits Processing header files
//
#include <list_processing/dynamic/import.hpp>


namespace ListProcessing::Dynamic::Details {

  template<typename F>
  concept thunk = requires(F f){
    f();
  };

  template<typename T>
  using Thunk = function<T()>;

  template<typename T>
  class Lazy {
    using thunk_type = Thunk<T>;
    using variant_type = variant<T, thunk_type>;
    using pointer_type = shared_ptr<variant_type>;

    mutable pointer_type ptr;
  public:

    using value_type = T;

    Lazy(T x) : ptr{make_shared<variant_type>(std::move(x))} {}

    Lazy(thunk_type f) : ptr{make_shared<variant_type>(std::move(f))} {}

    operator const T& () const {
      return holds_alternative<thunk_type>(*ptr)
	? reify()
	: get<value_type>(*ptr);
    }

    bool
    isLazy() const {
      return holds_alternative<thunk_type>(*ptr);
    }

    friend bool
    isLazy(Lazy x){
      return x.isLazy();
    }

    bool
    isReified() const {
      return ! isLazy();
    }

    friend bool
    isReified(Lazy x){
      return x.isReified();
    }


  private:

    const T&
    reify(){
      ptr = variant_type{get<thunk_type>(*ptr)()};
      return get<value_type>(*ptr);
    }

  };

  template<thunk F>
  auto
  lazy(F&& f){
    using T = std::remove_cvref_t<std::invoke_result_t<F>>;
    return Lazy<T>{f};
  }
}
