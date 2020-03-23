#pragma once

//
// ... List Processing header files
//
#include <list_processing/dynamic/import.hpp>

namespace ListProcessing::Dynamic::Details
{
  template<typename T, size_type N>
  class ChunkData
  {
    static_assert(is_default_constructible_v<T>);
    static_assert(N > 0);

  public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = value_type const&;
    using rvalue_reference = value_type&&;

    static constexpr size_type extent = N;

    ChunkData()
      : fillpoint(0)
    {}

    ChunkData(const_reference x)
      : fillpoint(1)
    {
      data[0] = x;
    }

    ChunkData(const_reference x, ChunkData&& xs)
      : data(move(xs.data))
      , fillpoint(xs.fillpoint)
    {
      assert(fillpoint < extent);
      data[fillpoint++] = x;
    }

    ChunkData(ChunkData&& input)
      : data(move(input.data))
      , fillpoint(input.fillpoint)
    {}

    ChunkData(ChunkData&& input, const_reference x)
      : data(move(input.data))
      , fillpoint(input.fillpoint)
    {
      data[fillpoint++] = x;
    }

    static shared_ptr<ChunkData>
    push(
      shared_ptr<ChunkData> xs,
      index_type index,
      const_reference value)
    {
      if (index == xs->fillpoint) {
        lock_guard<mutex> lock(xs->mex);
        if (index == xs->fillpoint) {
          xs->data[xs->fillpoint++] = value;
          return xs;
        } else {
          return fillNewChunk(xs, index, value);
        }
      } else {
        return fillNewChunk(xs, index, value);
      }
    }

    const_reference
    operator[](index_type index)
    {
      assert(index >= 0);
      assert(index < fillpoint);
      return data[index];
    }

  private:
    array<value_type, extent> data;
    index_type fillpoint;
    mutex mex;

    static shared_ptr<ChunkData>
    fillNewChunk(
      shared_ptr<ChunkData> xs,
      index_type index,
      const_reference value)
    {
      auto result = make_shared<ChunkData>();

      copy_n(begin(xs->data), index, begin(result->data));
      result->data[index] = value;
      result->fillpoint = index + 1;
      return result;
    }

    template<typename F, typename R = decay_t<result_of_t<F(T)>>>
    friend shared_ptr<ChunkData<R, N>>
    fMap(F f, ChunkData const& xs, index_type n)
    {
      auto result = make_shared<ChunkData<R, N>>();
      for (index_type i = 0; i < n; ++i) {
        result->data[i] = f(xs->data[i]);
      }
      result->fillpoint = n;
      return result;
    }

  }; // end of clas ChunkData

} // end of namespace ListProcessing::Dynamic::Details
