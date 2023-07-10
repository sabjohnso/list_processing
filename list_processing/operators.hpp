#pragma once

//
// ... ListProcessing header files
//
#include <list_processing/operators/Map.hpp>
#include <list_processing/operators/Pipe.hpp>
#include <list_processing/operators/ToList.hpp>

#include <list_processing/operators/ForceGet.hpp>
#include <list_processing/operators/HasData.hpp>
#include <list_processing/operators/HasKey.hpp>
#include <list_processing/operators/IsEmpty.hpp>
#include <list_processing/operators/MaybeGet.hpp>
#include <list_processing/operators/Remove.hpp>
#include <list_processing/operators/Set.hpp>
#include <list_processing/operators/TryGet.hpp>
#include <list_processing/operators/Unset.hpp>

#include <list_processing/operators/collection_operators.hpp>
#include <list_processing/operators/list_operators.hpp>
#include <list_processing/operators/queue_operators.hpp>
#include <list_processing/operators/stack_operators.hpp>
#include <list_processing/operators/tape_operators.hpp>

namespace ListProcessing::Operators {

  constexpr auto toList = Details::toList;

  constexpr auto pipe = Details::pipe;
  constexpr auto map = Details::map;

  constexpr auto hasData = Details::hasData;
  constexpr auto isEmpty = Details::isEmpty;

  constexpr auto set = Details::set;
  constexpr auto unset = Details::unset;
  constexpr auto forceGet = Details::forceGet;
  constexpr auto maybeGet = Details::maybeGet;
  constexpr auto tryGet = Details::tryGet;
  constexpr auto remove = Details::remove;
  constexpr auto hasKey = Details::hasKey;

  constexpr auto push = Details::push;
  constexpr auto top = Details::top;
  constexpr auto pop = Details::pop;
  constexpr auto pop2 = Details::pop2;
  constexpr auto pop3 = Details::pop3;
  constexpr auto dup = Details::dup;
  constexpr auto swap = Details::swap;
  constexpr auto nip = Details::nip;
  constexpr auto tuck = Details::tuck;
  constexpr auto over = Details::over;
  constexpr auto rot = Details::rot;
  constexpr auto app1 = Details::app1;
  constexpr auto app2 = Details::app2;

  constexpr auto isAtBack = Details::isAtBack;
  constexpr auto isAtFront = Details::isAtFront;
  constexpr auto insert = Details::insert;
  constexpr auto erase = Details::erase;
  constexpr auto write = Details::write;
  constexpr auto read = Details::read;
  constexpr auto position = Details::position;
  constexpr auto remaining = Details::remaining;
  constexpr auto fwd = Details::fwd;
  constexpr auto bwd = Details::bwd;
  constexpr auto moveBy = Details::moveBy;
  constexpr auto moveTo = Details::moveTo;
  constexpr auto toFront = Details::toFront;
  constexpr auto toBack = Details::toBack;
  constexpr auto splice = Details::splice;

  using Details::HasHead;
  using Details::HasTail;

  constexpr auto head = Details::head;
  constexpr auto tail = Details::tail;
  constexpr auto listRef = Details::listRef;
  constexpr auto append = Details::append;
  constexpr auto mapList = Details::mapList;
  constexpr auto fApplyList = Details::fApplyList;
  constexpr auto flatMapList = Details::flatMapList;
  constexpr auto flattenList = Details::flattenList;
  constexpr auto filter = Details::filter;
  constexpr auto sort = Details::sort;

} // end of namespace ListProcessing::Operators
