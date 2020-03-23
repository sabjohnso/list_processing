#pragma once

//
// ... List Processing header files
//
#include <list_processing/dynamic/ChunkData.hpp>
#include <list_processing/dynamic/import.hpp>

namespace ListProcessing::Dynamic::Details
{
  template<typename T, size_type N>
  class Chunk
  {

  public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = value_type const&;
    using rvalue_reference = value_type&&;

    static constexpr size_type extent = N;

    using Data = ChunkData<value_type, extent>;

    Chunk() = delete;

    Chunk(Chunk const& input, bool reverse = false)
      : ptr(input.ptr)
      , fillpoint(input.fillpoint)
      , reversed(reverse ? !input.reversed : input.reversed)
    {}

    Chunk(Chunk const& input, index_type new_fillpoint)
      : ptr(input.ptr)
      , fillpoint(new_fillpoint)
      , reversed(input.reversed)
    {
      assert(fillpoint > 0);
      assert(fillpoint < extent);
      assert(fillpoint <= input.fillpoint);
    }

    Chunk(const_reference x)
      : ptr(make_shared<Data>(x))
      , fillpoint(1)
      , reversed(false)
    {}

    Chunk(const_reference x, Chunk const& xs)
      : ptr(Data::push(xs.ptr, xs.fillpoint, x))
      , fillpoint(xs.fillpoint + 1)
      , reversed(false)
    {}

    friend value_type
    head(Chunk xs)
    {
      return chunkDataRef(*xs.ptr, xs.fillpoint - 1);
    }

    const_reference
    operator[](index_type index)
    {
      assert(index >= 0);
      assert(index < fillpoint);
      return (*ptr)[reversed ? (fillpoint - index - 1) : index];
    }

    friend size_type
    length(Chunk xs)
    {
      return xs.fillpoint;
    }

    friend bool
    isFull(Chunk xs)
    {
      return xs.fillpoint == extent;
    }

    template<typename F, typename R = decay_t<result_of_t<F(T)>>>
    friend Chunk<R, N>
    fMap(F f, Chunk xs)
    {
      Chunk<R, N> result();
      result.ptr = fMap(f, *xs.ptr, xs.fillpoint);
      result.ptr = xs.fillpoint;
      return result;
    }

    shared_ptr<Data> ptr;
    index_type fillpoint;
    bool reversed;
  };

} // end of namespace ListProcessing::Dynamic::Details
