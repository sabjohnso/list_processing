#pragma once

//
// ... ListProcessing header files
//
#include <list_processing/operators/HasData.hpp>
#include <list_processing/operators/IsEmpty.hpp>
#include <list_processing/operators/Set.hpp>
#include <list_processing/operators/Unset.hpp>
#include <list_processing/operators/ForceGet.hpp>
#include <list_processing/operators/MaybeGet.hpp>
#include <list_processing/operators/TryGet.hpp>
#include <list_processing/operators/Remove.hpp>
#include <list_processing/operators/HasKey.hpp>

#include <list_processing/operators/stack_operators.hpp>

namespace ListProcessing::Operators
{

  static constexpr auto hasData  = Details::hasData;
  static constexpr auto isEmpty  = Details::isEmpty;

  static constexpr auto set      = Details::set;
  static constexpr auto unset    = Details::unset;
  static constexpr auto forceGet = Details::forceGet;
  static constexpr auto maybeGet = Details::maybeGet;
  static constexpr auto tryGet   = Details::tryGet;
  static constexpr auto remove   = Details::remove;
  static constexpr auto hasKey   = Details::hasKey;

  static constexpr auto push     = Details::push;
  static constexpr auto top      = Details::top;
  static constexpr auto pop      = Details::pop;
  static constexpr auto drop     = Details::drop;
  static constexpr auto drop2    = Details::drop2;
  static constexpr auto drop3    = Details::drop3;
  static constexpr auto dup      = Details::dup;
  static constexpr auto swap     = Details::swap;
  static constexpr auto nip      = Details::nip;
  static constexpr auto tuck     = Details::tuck;
  static constexpr auto over     = Details::over;
  static constexpr auto rot      = Details::rot;
  static constexpr auto app1     = Details::app1;
  static constexpr auto app2     = Details::app2;

} // end of namespace ListProcessing::Operators
