#pragma once

//
// ... List Processing header files
//
// #include <list_processing/dynamic/Cell.hpp>

#include <list_processing/dynamic/List.hpp>
#include <list_processing/dynamic/Stack.hpp>
#include <list_processing/dynamic/Zipper.hpp>

namespace ListProcessing::Dynamic
{

  using Details::buildList;
  using Details::list;
  using Details::nil;

  using Details::empty_stack;
  using Details::pipe;
  using Details::Stack;

  using Details::empty_zipper;
  using Details::zipper;

} // end of namespace ListProcessing::Dynamic
