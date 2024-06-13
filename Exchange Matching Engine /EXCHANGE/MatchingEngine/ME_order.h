//
// Created by Ranjan shahaji shitole on 13/06/24.
//

#pragma once
#include <array>
#include <sstream>
#include "Exchange Matching Engine /Common Files/types.h"

using namespace Common;

namespace Exchange{
    struct MEOrder {
        TickerId ticker_Id_ = TickerId_INVALID;
        ClientId client_id_ = ClientId_INVALID;
        OrderId client_order_id_ = OrderId_INVALID;
        OrderId market_order_id_ = OrderId_INVALID;
        Side side_ = Side::INVALID;
        Price price_ = Price_INVALID;
        Qty qty_ = Qty_INVALID;
        Priority priority_ = Priority_INVALID;
        MEOrder *prev_order_ = nullptr;
        MEOrder *next_order_ = nullptr;
        MEOrder()=default;

        MEOrder(TickerId ticker_id, ClientId client_id, OrderId client_order_id, OrderId market_order_id, Side side,
                Price price, Qty qty, Priority priority, MEOrder *prev_order, MEOrder *next_order)

        noexcept
                : ticker_id_(ticker_id),
        client_id_(client_id),
        client_order_id_(client_order_id),
        market_order_id_(market_order_id),
        side_(side),
        price_(price),
        qty_(qty),
        priority_(priority),
        prev_order_(prev_order),
        next_order_(next_order) {}

        auto toString() const -> std::string;

        typedef std::array<MEOrder *,ME_MAX_ORDER_IDS> OrderHashMap;
        typedef std::array<OrderHashMap,ME_MAX_NUM_CLIENTS> ClientOrderHashMap;

        struct MEOrderAtPrice {
            Side side_ = Side::INVALID;
            Price price_ = Price_INVALID;

            MEOrderAtPrice *prev_entry_ = nullptr;
            MEOrderAtPrice *next_entry_ = nullptr;

            MEOrderAtPrice() = default;

            MEOrderAtPrice(Side side, Price price, MEOrder *first_me_order, MEOrderAtPRice *prev_entry,
                           MEOrderAtPrice *next_entry)
                    : side_(side), price_(price), first_me_order(first_me_order), prev_entry_(prev_entry),
                      next_entry_(next_entry) {}


            auto toString() const {
                std::stringstream ss;
                ss << "MEOrderAtPrice[ "
                   << "side :" << sideToString(side_) << " "
                   << "price : " << priceToString(price_) << " "
                   << "first_me_order : " << first_me_order_ ? first_me_order_ - toString() : "null" << " "
                                                                                                     << "prev :"
                                                                                                     << priceToString(
                                                                                                             prev_entry_
                                                                                                             ? prev_entry_->Price_INVALID)
                                                                                                     << " "
                                                                                                     << "next :"
                                                                                                     << priceToString(
                                                                                                             next_entry_
                                                                                                             ? next_entry->price_
                                                                                                             : Price_INVALID)
                                                                                                     << "]";
                return ss.str();

            }
        }


    };
    typedef std::array<MEOrderAtPrice * ,ME_MAX_PRICE_LEVELS> OrdersAtPriceHashMap;







}