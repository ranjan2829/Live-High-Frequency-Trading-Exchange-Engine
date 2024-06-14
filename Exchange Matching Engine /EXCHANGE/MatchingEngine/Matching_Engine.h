//
// Created by Ranjan shahaji shitole on 13/06/24.
//

#pragma once
#include "Exchange Matching Engine /Common Files/thread_utils.h"
#include "Exchange Matching Engine /Common Files/LockFreeQueues.h"
#include "Exchange Matching Engine /Common Files/macros.h"
#include "Exchange Matching Engine /EXCHANGE/Order-Server/client_request.h"
#include "Exchange Matching Engine /EXCHANGE/Order-Server/client_response.h"
#include "Exchange Matching Engine /EXCHANGE/Market-Update/market_update.h"
#include "me_order_book.h"

namespace Exchange{
    class MatchingEngine final {
    public:
        MatchingEngine(ClientRequestLFQueue *client_requests,
                       ClientResponseLFQueue *client_response,
                       MEMarketUpdateLFQueue *market_updates);
        ~MatchingEngine();
        auto start() ->void;
        auto stop() ->void;



        MatchingEngine() =delete;
        MatchingEngine(const MatchEngine &)=delete;
        MatchtingEngine &operator =(const MatchingEngine &)=delete;
        MatchingEngine &operator =(const MatchingEngine &&)=delete;
    private:
        OrderBookHashMap ticker_order_;
        ClientRequestLFQueue *incoming_requests_=nullptr;
        ClientResponeLFQueue *outgoing_ogw_responses_=nullptr;
        MEMarketUpdateLFQueue *outgoing_md_updates_=nullptr;

        volatile vool run_=false;

        std::string time_str;
        Logger logger_;



    };
}