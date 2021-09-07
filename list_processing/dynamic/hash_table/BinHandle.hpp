#pragma once

namespace ListProcessing::Dynamic::Details {

  template<typename Key, typename Mapped, size_type BinSizeExponent>
  class BinHandle
    : public enable_shared_ptr_from_this<
        BinHandle<Key, Mapped, BinSizeExponent>>
  {
  public:
  private:
    using bin_type = Bin<Key, Mapped, BinSizeExponent>;
    using bin_pointer = shared_ptr<bin_type>;

    bin_pointer pbin;

  }; // end of class BinHandle

} // end of namespace ListProcessing::Dynamic::Details
