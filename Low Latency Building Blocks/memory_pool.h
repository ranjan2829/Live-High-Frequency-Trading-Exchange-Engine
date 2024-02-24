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
                ASSERT(obj_block)
            }
}