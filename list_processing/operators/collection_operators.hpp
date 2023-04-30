#pragma once

namespace ListProcessing::Operators::Details {

  template<typename T, typename S>
  concept HasDrop = requires(S&& n, T&& xs) {
                      {
                        std::forward<T>(xs).drop(std::forward<S>(n))
                      };
                    };

  class Drop : public Static_curried<Drop, Nat<2>>
  {
  public:
    template<typename S, HasDrop<S> T>
    static constexpr auto
    call(S&& n, T&& xs)
    {
      return std::forward<T>(xs).drop(std::forward<S>(n));
    }
  } constexpr drop{};

  template<typename T, typename S>
  concept HasTake = requires(S&& n, T&& xs) {
                      {
                        std::forward<T>(xs).take(std::forward<S>(n))
                      };
                    };

  class Take : public Static_curried<Take, Nat<2>>
  {
  public:
    template<typename S, HasTake<S> T>
    static constexpr auto
    call(S&& n, T&& xs)
    {
      return std::forward<T>(xs).take(std::forward<S>(n));
    }
  } constexpr take{};

} // end of namespace ListProcessing::Operators::Details
