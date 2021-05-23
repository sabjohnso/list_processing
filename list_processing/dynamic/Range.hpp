#pragma once

//
// ... List Processing header files
//
#include <list_processing/dynamic/import.hpp>

namespace ListProcessing::Dynamic::Details {

  struct RangeData {
    index_type start;
    index_type stop;
    index_type step;
  };

  class Range;

  class RangeIterator {
  public:
    operator index_type() const;

    RangeIterator
    next() const;

    bool
    done() const;

  private:
    friend class Range;
    RangeIterator() = delete;
    RangeIterator(RangeIterator const& input);
    RangeIterator(
      shared_ptr<const RangeData> input_pointer,
      index_type                  input_offset);
    shared_ptr<const RangeData> ptr;
    index_type                  offset;
  };

  class Range {
  public:
    Range() = delete;
    Range(index_type stop);
    Range(index_type start, index_type stop);
    Range(index_type start, index_type stop, index_type step);

  private:
    shared_ptr<const RangeData> ptr;
  };

} // end of namespace ListProcessing::Dynamic::Details
