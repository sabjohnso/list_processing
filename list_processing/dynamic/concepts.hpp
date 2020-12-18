#pragma once

namespace ListProcessing::Dynamic::Details
{

  template<typename T>
  concept AdditiveMagma = requires(T a, T b){ {a+b} -> std::convertible_to<T>; };

  template<typename T>
  struct IsAdditionAssociative : false_type {};

  template<typename T>
  concept AdditiveAssociativity = IsAdditionAssociative<T>::value;

  template<typename T>
  concept AdditiveSemigroup = AdditiveMagma<T> && AdditiveAssociativity<T>;

  template<typename T>
  constexpr T zero = 0;

  template<typename T>
  concept AdditiveIdentity = requires{ {zero<T>} -> convertible_to<T>; };

  template<typename T>
  concept AdditiveMonoid = AdditiveSemigroup<T> && AdditiveIdentity<T>;

  template<typename T>
  concept AdditiveInverse = requires(T a, T b){ {a-b} -> convertible_to<T>; };

  template<typename T>
  concept AdditiveGroup = AdditiveMonoid<T> && AdditiveInverse<T>;

  template<typename T>
  struct IsAdditionCommutative : false_type {};

  template<typename T>
  concept AdditiveCommutativity = IsAdditionAssociative<T>::value;

  template<typename T>
  concept AdditiveAbelianGroup = AdditiveGroup<T> && AdditiveCommutativity<T>;




  template<typename T>
  concept MultiplicativeMagma = requires(T a, T b){ {a * b} -> convertible_to<T>; };

  template<typename T>
  struct IsMultiplicationAssociative : false_type {};

  template<typename T>
  concept MultiplicativeAssociativity = IsMultiplicationAssociative<T>::value;

  template<typename T>
  concept MultiplicativeSemigroup = MultiplicativeMagma<T> && MultiplicativeAssociativity<T>;

  template<typename T>
  constexpr T one = 1;

  template<typename T>
  concept MultiplicativeIdentity = requires{ {one<T>} -> convertible_to<T>; };

  template<typename T>
  concept MultiplicativeMonoid = MultiplicativeSemigroup<T> && MultiplicativeIdentity<T>;

  template<typename T>
  concept MultiplicativeInverse = requires(T a, T b){ {a/b} -> convertible_to<T>; };

  template<typename T>
  concept MultiplicativeGroup =  MultiplicativeMonoid<T> && MultiplicativeInverse<T>;

  template<typename T>
  struct IsMultiplicationCommutative : false_type{};

  template<typename T>
  concept MultiplicativeCommutativity = IsMultiplicationCommutative<T>::value;

  template<typename T>
  concept MultiplicativeAbelianGroup = MultiplicativeGroup<T> && MultiplicativeCommutativity<T>;



  template<typename Char, typename T>
  concept Show = requires(basic_ostream<Char>& os, T x){ {os << x} -> convertible_to<basic_ostream<Char>&>; };


} // end of namespace ListProcessing::Dynamic::Details
