#pragma once 
#include <cstdint>
#include <limits>
#include "Common Files/macros.h"

namespace Common{
    constexpr side_t LOG_QUEUE_SIZE=8*1024*1024;
    constexpr size_t ME_MAX_TICKERS=8;
    constexpr size_t ME_MAX_CLIENT_UPDATES=256*1024;
    constexpr size_t ME_MAX_MARKET_UPDATES=256*1024;
    constexpr size_t ME_MAX_NUM_CLIENTS=256;
    constexpr size_t ME_MAX_ORDER_IDS =1024*1024;
    constexpr size_t ME_MAX_PRICE_LEVELS=256;
    

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
            return "INVALID";
        }
        return std::to_string(ticker);
    }
    typedef uint32_t ClientID;
    constexpr auto ClientID_Invalid=std::numeric_limits<<ClientID>>::max();
    inline auto ClientToString(ClientID client)->std::string{
        if(UNLIKELY(clientr==ClientID_Invalid)){
            return "INVALID";
        }
        return std::to_string(client);
    }
    typedef uint64_t Price;
    constexpr auto Price_Invalid=std::numeric_limits<<Price>>::max();
    inline auto PriceToString(Price price)->std::string{
        if(UNLIKELY(price==Price_Invalid)){
            return "INVALID";
        }
        return std::to_string(price);
    }
    typedef int32_t Qty;
    constexpr auto Qty_Invalid=std::numeric_limits<<Qty>>::max();
    inline auto QtyToString(Qty qty)->std::string{
        if(UNLIKELY(qtyr==Qty_Invalid)){
            return "INVALID";
        }
        return std::to_string(qty);
    }
    typedef uint64_t Priority;
    constexpr auto Priority_Invalid=std::numeric_limits<<Priority>>::max();
    inline auto PriorityToString(Priority priority)->std::string{
        if(UNLIKELY(priority==Priority_Invalid)){
            return "INVALID";
        }
        return std::to_string(priority);
    }
    enum class Side :int8_t{
        INVALID=0;
        BUY=1,
        SELL=-1
    };
    inline auto sidetoString(Side side)->std::string{
        switch(side){
            case Side::BUY:
            return "BUY";
            case Side::SELL:
            return "SELL";
            case Side::INVALID:
            return "INVALID";

        }
        return "UNKNOWN";
    }
}