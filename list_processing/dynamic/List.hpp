#pragma once

//
// ... List Processing' header files
//
#include <list_processing/dynamic/List1.hpp>
#include <list_processing/dynamic/ListFwd.hpp>
#include <list_processing/dynamic/ListN.hpp>
#include <list_processing/dynamic/ListOperators.hpp>
#include <list_processing/dynamic/ListTraits.hpp>
#include <list_processing/dynamic/Nil.hpp>
#include <list_processing/dynamic/ShortList.hpp>
#include <list_processing/dynamic/import.hpp>

namespace ListProcessing::Dynamic::Details {

  /**
   * @brief Construct a list from the input values
   */
  class ListConstructor : public Static_callable<ListConstructor> {
  public:
    template<typename... Ts>
    static constexpr auto
    call(Ts&&... xs) {
      if constexpr (bool(count_types<Ts...>())) {
        using T = common_type_t<decay_t<Ts>...>;
        return listOf<T>(forward<Ts>(xs)...);

      } else {
        return Nil{};
      }
    }

    template<typename T>
    static List<T>
    listOf() {
      return nil<T>;
    }

    template<typename T, typename T1, typename... Ts>
    static List<T>
    listOf(T1&& x1, Ts&&... xs) {
      return cons(forward<T1>(x1), listOf<T>(forward<Ts>(xs)...));
    }
  } constexpr list{};

  /**
   * @brief Build a list of the results of applying the  input function
   * to each value in the half open range [0, n).
   */
  class BuildList : public Static_curried<BuildList, Nat<2>> {
  public:
    template<
      typename F,
      typename T      = decay_t<result_of_t<F(index_type)>>,
      typename Result = ListType<T>>
    static Result
    call(F&& f, size_type n) {
      return buildListAux(forward<F>(f), n, Result::nil);
    }
  } constexpr buildList{};

} // end of namespace ListProcessing::Dynamic::Details
