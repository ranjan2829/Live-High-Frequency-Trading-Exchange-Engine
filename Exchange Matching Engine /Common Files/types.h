#pragma once 
#include <cstdint>
#include <limits>
#include "Common Files/macros.h"

namespace Common{
    typedef uint64_t OrderId;
    constexpr auto OrderId_Invalid=std::numeric_limits<OrderId>>::max();
    inline auto orderToString(OrderId order)->std::string{
        if(UNLIKELY(order==OrderId_Invalid)){
            return "INVALID";
        }
        return std::to_string(order);
    }
    typedef uint32_t TickerID;
    constexpr auto TickerID_Invalid=std::numeric_limits<<TickerID>>::max();
    inline auto TickerToString(TickerID ticker)->std::string{
        if(UNLIKELY(ticker==TickerID_Invalid)){
            return "IVALID";
        }
        return std::to_string(ticker);
    }
    typedef uint32_t ClientID;
    constexpr auto ClientID_Invalid=std::numeric_limits<<ClientID>>::max();
    inline auto ClientToString(ClientID client)->std::string{
        if(UNLIKELY(clientr==ClientID_Invalid)){
            return "IVALID";
        }
        return std::to_string(client);
    }
}