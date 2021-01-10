#pragma once

//
// ... List Processing header files
//
#include <list_processing/dynamic/Nil.hpp>
#include <list_processing/dynamic/List.hpp>
#include <list_processing/dynamic/Stack.hpp>
#include <list_processing/dynamic/Tape.hpp>
#include <list_processing/dynamic/Queue.hpp>
#include <list_processing/dynamic/Tree.hpp>
#include <list_processing/dynamic/AList.hpp>
#include <list_processing/dynamic/piping.hpp>
#include <list_processing/dynamic/Value.hpp>
#include <list_processing/dynamic/Stream.hpp>

namespace ListProcessing::Dynamic
{
  using Details::index_type;
  using Details::integer;
  using Details::offset_type;
  using Details::size_type;

  using Details::buildList;
  using Details::list;
  using Details::ListType;
  using Details::List;
  using Details::nil;
  using Details::Nil;

  using Details::empty_stack;
  using Details::Stack;

  using Details::empty_tape;
  using Details::tape;

  using Details::empty_queue;
  using Details::queue;

  using Details::empty_tree;

  using Details::empty_alist;

  using Details::Shared;
  using Details::sharedList;

  using Details::Stream;
  using Details::empty_stream;
  using Details::streamOf;
  using Details::stream;
  using Details::buildStream;
  using Details::iterate;


} // end of namespace ListProcessing::Dynamic
