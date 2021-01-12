#pragma once

//
// ... List Processing header files
//
#include <list_processing/compile_time/Cell.hpp>
#include <list_processing/compile_time/Nothing.hpp>
#include <list_processing/compile_time/Queue.hpp>
#include <list_processing/compile_time/Stack.hpp>
#include <list_processing/compile_time/Tree.hpp>
#include <list_processing/compile_time/Tape.hpp>

namespace ListProcessing::CompileTime
{
  using Details::idx;

  using Details::cons;
  using Details::list;
  using Details::nothing;
  using Details::length_;
  using Details::ListType;
  using Details::buildList;

  using Details::empty_stack;
  using Details::make_stack;

  using Details::empty_tape;
  using Details::makeTape;

  using Details::empty_queue;
  using Details::makeQueue;

  using Details::empty_tree;
  using Details::tree;

} // end of namespace ListProcessing::CompileTime
