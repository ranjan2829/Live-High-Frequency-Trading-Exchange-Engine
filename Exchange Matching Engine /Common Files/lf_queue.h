#pragma once

#include <iostream>
#include <vector>
#include <atomic>
#include <thread>

#include "macros.h"

namespace Common {
  template<typename T>
  class LFQueue final {
  public:
    explicit LFQueue(std::size_t num_elems) :
        store_(num_elems, T()) /* pre-allocation of vector storage. */ {
      // Ensure size is power of 2 for efficient modulo operations
      ASSERT((num_elems & (num_elems - 1)) == 0, "LFQueue size must be power of 2");
    }

    auto getNextToWriteTo() noexcept -> T* {
      auto current_write = write_pos_.load(std::memory_order_relaxed);
      auto next_write = (current_write + 1) & (store_.size() - 1); // Fast modulo for power of 2
      
      // Check if queue is full
      if (next_write == read_pos_.load(std::memory_order_acquire)) {
        return nullptr; // Queue full
      }
      
      return &store_[current_write];
    }

    auto updateWriteIndex() noexcept -> bool {
      write_pos_.fetch_add(1, std::memory_order_release);
      return true;
    }

    auto getNextToRead() const noexcept -> const T * {
      auto current_read = read_pos_.load(std::memory_order_relaxed);
      
      if (current_read == write_pos_.load(std::memory_order_acquire)) {
        return nullptr; // Queue empty
      }
      
      return &store_[current_read];
    }

    auto updateReadIndex() noexcept -> bool {
      auto current_read = read_pos_.load(std::memory_order_relaxed);
      
      if (current_read == write_pos_.load(std::memory_order_acquire)) {
        return false; // Queue empty
      }
      
      read_pos_.fetch_add(1, std::memory_order_release);
      return true;
    }

    auto size() const noexcept -> size_t {
      auto write_pos = write_pos_.load(std::memory_order_relaxed);
      auto read_pos = read_pos_.load(std::memory_order_relaxed);
      return (write_pos - read_pos) & (store_.size() - 1);
    }

    /// Deleted default, copy & move constructors and assignment-operators.
    LFQueue() = delete;

    LFQueue(const LFQueue &) = delete;

    LFQueue(LFQueue &&) = delete;

    LFQueue &operator=(const LFQueue &) = delete;

    LFQueue &operator=(LFQueue &&) = delete;

  private:
    /// Underlying container of data accessed in FIFO order.
    std::vector<T> store_;

    /// Atomic trackers for write and read positions with proper memory alignment
    alignas(64) std::atomic<size_t> write_pos_ = {0};
    alignas(64) std::atomic<size_t> read_pos_ = {0};
  };
}
