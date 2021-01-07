#pragma once

//
// ... ListProcessing header files
//
#include <list_processing/operators/Pipe.hpp>

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

  constexpr auto pipe     = Details::pipe;

  constexpr auto hasData  = Details::hasData;
  constexpr auto isEmpty  = Details::isEmpty;

  constexpr auto set      = Details::set;
  constexpr auto unset    = Details::unset;
  constexpr auto forceGet = Details::forceGet;
  constexpr auto maybeGet = Details::maybeGet;
  constexpr auto tryGet   = Details::tryGet;
  constexpr auto remove   = Details::remove;
  constexpr auto hasKey   = Details::hasKey;

  constexpr auto push     = Details::push;
  constexpr auto top      = Details::top;
  constexpr auto pop      = Details::pop;
  constexpr auto drop     = Details::drop;
  constexpr auto drop2    = Details::drop2;
  constexpr auto drop3    = Details::drop3;
  constexpr auto dup      = Details::dup;
  constexpr auto swap     = Details::swap;
  constexpr auto nip      = Details::nip;
  constexpr auto tuck     = Details::tuck;
  constexpr auto over     = Details::over;
  constexpr auto rot      = Details::rot;
  constexpr auto app1     = Details::app1;
  constexpr auto app2     = Details::app2;

} // end of namespace ListProcessing::Operators
