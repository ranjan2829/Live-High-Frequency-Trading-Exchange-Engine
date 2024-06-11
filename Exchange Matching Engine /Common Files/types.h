#pragma once 
#include <cstdint>
#include <limits>
#include "Common Files/macros.h"
namespace Common{
    typedef uint64_t orderId;
    contexpr auto orderId_invalid=std::numeric_limits<orderId>>::max();
    inline auto orderIdToString(orderId order)->std::string{
        if(UNLIKELY(order == orderId_invalid)){
            return "INVALID";
        }
        return std::to_string(order);
    }

}