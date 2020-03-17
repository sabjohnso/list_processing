#include <list_processing/dynamic/Range.hpp>

//
// ... List Processing header files
//
#include <list_processing/dynamic/import.hpp>

namespace ListProcessing::Dynamic::Details {

  Range::Range(index_type stop)
    : ptr(make_shared<const RangeData>(RangeData{ 0, stop, 1 }))
  {}

  Range::Range(index_type start, index_type stop)
    : ptr(make_shared<const RangeData>(
        RangeData{ start, stop, (stop >= start ? 1 : -1) }))
  {}

  Range::Range(index_type start, index_type stop, index_type step)
    : ptr(make_shared<const RangeData>(RangeData{ start, stop, step }))
  {}

  RangeIterator::RangeIterator(RangeIterator const& input)
    : ptr(input.ptr)
    , offset(input.offset)
  {}

  RangeIterator::RangeIterator(
    shared_ptr<const RangeData> input_pointer,
    index_type input_offset)
    : ptr(input_pointer)
    , offset(input_offset)
  {}

} // end of namespace ListProcessing::Dynamic::Details
