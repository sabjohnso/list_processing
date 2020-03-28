#pragma once

//
// ... List Processing header files
//
// #include <list_processing/dynamic/Cell.hpp>

#include <list_processing/dynamic/List.hpp>
#include <list_processing/dynamic/Stack.hpp>
#include <list_processing/dynamic/Tape.hpp>

namespace ListProcessing::Dynamic
{
  using Details::index_type;
  using Details::integer;
  using Details::offset_type;
  using Details::size_type;

  using Details::buildList;
  using Details::list;
  using Details::nil;

  using Details::empty_stack;
  using Details::pipe;
  using Details::Stack;

  using Details::empty_tape;
  using Details::tape;

} // end of namespace ListProcessing::Dynamic
