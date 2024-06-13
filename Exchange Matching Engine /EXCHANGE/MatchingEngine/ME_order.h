//
// Created by Ranjan shahaji shitole on 13/06/24.
//

#pragma once
#include <array>
#include <sstream>
#include "Exchange Matching Engine /Common Files/types.h"

using namespace Common;

namespace Exchange{
    struct MEOrder{
        TickerId ticker_Id_=TickerId_INVALID;
        ClientId client_id_=ClientId_INVALID;
        OrderId client_order_id_=OrderId_INVALID;
        OrderId market_order_id_=OrderId_INVALID;
        Side side_=Side::INVALID;
        Price price_=Price_INVALID;
        Qty qty_=Qty_INVALID;
        Priority priority_ =Priority_INVALID;
        MEOrder *prev_order_=nullptr;
        MEOrder *nest_order_=nullptr;


        MEOrder()=default;


    };
};