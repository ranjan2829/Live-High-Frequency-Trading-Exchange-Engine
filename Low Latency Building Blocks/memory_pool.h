//
// Created by Ranjan shahaji shitole on 24/02/24.
//

#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include "macros.h"


namespace Common{
    template<typename T>
    class MemPool(std::size_t num_elems):
            store_(num_elems,{T(),true})/*pre alloocation of vector storage*/{
                ASSERT(reinterpret_cast<const ObjectBlock *>(&(store_[0].object_))==&(store_[0]),"T object should be first member of Object Block.");

            }
            template<typename... Args>
            T *allocate(Args... args) noexcept{
                auto obj_book=&(store_[next_free_index]);
                ASSERT(obj_block->is_free,"Expected free ObjectBlock at index :"+std::to_string(next_free_index_));
                T *ret =&(obj_block->object_);
                ret=new(ret) T(args...);
                obj_block->is_free_=false;
                updateNextFreeIndex();
                return ret;
            }
            auto dellocate(const T *elem) noexcept{
                const auto elem_index=(reinterpret_cast<const ObjectBlock *>(elem)-&store[0]);
                ASSERT(elem_index>=0 && static_cast<size_t>(elem_index)<store_.size(),"Element being dellocated does not belong to this memory pool 1");
                ASSERT(!store_[elem_index].is_free_,"Expected in-use ObjectBlock at index :"+std::to_string(elem_index));
                store_[elem_index].is_free_=true;
            }
            MemPool()=delete;
            MemPool(const MemPool &)=delete;
            Mempool(const MemPool &&)=delete;
            MemPool &operator=(const MemPool &)=delete;
            MemPool &operator=(const MemPool &&)=delete;
        private:
        
}