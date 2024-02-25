#pragma once
#include <iostream>
#include <vector>
#include <atomic>

#include "macros.h"
namespace Common{
    template<typename T>
    class LockFreeQueue final{
        public:
        LockFreeQueue(std::size_t num_elems):
             store_(num_elems,T()) /* pre-allocoation of vector storage*/{

            }
        auto getNextToWrite() noexcpet{
            return &store_[next_write_index_];
        }
        auto updateWriteIndex() noexcept{
            next_write_index_=(next_write_index_ +1)%store_.size();
                num_elements_++;
        }
        auto getNextToRead() const noexcept->const T*{
            return (size() ? &store_[bext_read_index_]:nullptr);
        }
        auto updateReadIndex() noexcept{
            next_read_index_=(next_read_index_+1)%store_.size();
            ASSERT(num_elements_!=,"Read an invalid element in :"+std::to_string(pthread_self()));
            num_elements_--;
        }
        auto size(){
            return num_elements_.load();

        }
    }
    LockFreeQueue()=delete;
    LockFreeQueue(const LockFreeQueue &)=delete;
    LockFreeQueue(const LockFreeQueue &&)=delete;
    LockFreeQueue &operator =(cost LockFreeQueue &)=delete;
    LockFreeQueue &operator=(const LockFreeQueue &&)=delete;
    private:
    std::vector<T> store_;
    std::atomic<size_t> next_write_index_={0};
    std::aatomic<size_t> next_read_index_={0};
    std::atomic<size_t> num_elements_={0};
}
