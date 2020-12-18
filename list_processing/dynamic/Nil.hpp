#pragma once

//
// ... Listprocessing header files
//
#include <list_processing/dynamic/import.hpp>
#include <list_processing/dynamic/ListFwd.hpp>

namespace ListProcessing::Dynamic::Details
{

  struct Nil{
    friend size_type
    length(Nil){ return 0; }

    friend Nil
    rappend(Nil, Nil){ return Nil{}; }

    friend Nil
    append(Nil, Nil){ return Nil{}; }

    friend Nil
    reverse(Nil){ return Nil{}; }

    template<typename F, typename U>
    friend U
    foldL(F, U const& init, Nil){ return init; }

    template<typename F, typename U>
    friend U
    foldR(F, Nil, U const& init){ return init; }

    template<typename F>
    friend Nil
    fMap(F, Nil){ return Nil{}; }

    friend Nil
    aMap(Nil, Nil){ return Nil{}; }

    friend Nil
    drop(Nil, size_type){ return Nil{}; }

    friend Nil
    take(Nil, size_type){ return Nil{}; }

    friend bool
    operator ==(Nil, Nil){ return true; }

    friend bool
    operator !=(Nil, Nil){ return false; }

    template<typename F>
    friend F
    doList(Nil, F f){ return f; }

    friend bool
    hasData(Nil){ return false; }

    friend bool
    isNull(Nil){ return true; }

    friend Nil
    tail(Nil){ return Nil{}; }

    template<typename T>
    friend auto
    cons(T&& x, Nil){
      return cons(forward<T>(x), nil<decay_t<T>>);
    }

  };



}
