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

namespace ListProcessing::Dynamic
{
  using Details::index_type;
  using Details::integer;
  using Details::offset_type;
  using Details::size_type;

  using Details::buildList;
  using Details::list;
  using Details::nil;
  using Details::Nil;

  using Details::empty_stack;
  using Details::pipe;
  using Details::Stack;

  using Details::empty_tape;
  using Details::tape;

  using Details::empty_queue;
  using Details::queue;

  using Details::empty_tree;

  using Details::empty_alist;

  using Details::Shared;
  using Details::sharedList;
  using Details::sharedListOf;


} // end of namespace ListProcessing::Dynamic
