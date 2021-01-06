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

namespace ListProcessing::Operators
{
  static constexpr auto hasData = Details::hasData;
  static constexpr auto isEmtpy = Details::isEmpty;

  static constexpr auto set = Details::set;
  static constexpr auto unset = Details::unset;
  static constexpr auto forceGet = Details::forceGet;
  static constexpr auto maybeGet = Details::maybeGet;
  static constexpr auto tryGet = Details::tryGet;
  static constexpr auto remove = Details::remove;
  static constexpr auto hasKey = Details::hasKey;

} // end of namespace ListProcessing::Operators
