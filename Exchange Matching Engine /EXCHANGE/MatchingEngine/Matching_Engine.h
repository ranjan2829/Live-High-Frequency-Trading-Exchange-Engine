//
// Created by Ranjan shahaji shitole on 13/06/24.
//

#pragma once
#include "LockFreeQueues.h"
#include "macros.h"
#include "thread_utils.h"
#include "market_update.h"
#include "client_request.h"
#include "client_response.h"
#include "LockFreeQueues.h"
#include "me_order_book.h"

namespace Exchange {
class MatchingEngine final {
public:
  MatchingEngine(ClientRequestLFQueue *client_requests,
                 ClientResponseLFQueue *client_response,
                 MEMarketUpdateLFQueue *market_updates);
  ~MatchingEngine();
  auto start() -> void;
  auto stop() -> void;

  auto processClientRequest(const MEClientRequest *client_request) noexcept {
    auto order_book = ticker_order_book_[client_request->ticker_id_];
    switch (client_request->type_) {
    case ClientRequestType::NEW: {
      order_book->add(client_request->client_id_, client_request->order_id_,
                      client_request->ticker_id_, client_request->side_,
                      client_request->price_, client_request->qty_);
    } break;

    case ClientRequestType::CANCEL: {
      order_book->cancel(client_request->client_id_, client_request->order_id_,
                         client_request->ticker_id_);
    } break;

    default: {
      FATAL("Received invalid client-request-type:" +
            clientRequestTypeToString(client_request->type_));
    } break;
    }
  }
  auto sendClientResponse(const MEClientResponse *client_response) noexcept {
    logger_.log("%:% %() % Sending %\n", __FILE__, __LINE__, __FUNCTION__,
                Common::getCurrentTimeStr(&time_str_),
                client_response->toString());

    auto next_write = outgoing_ogw_responses_->getNextToWriteTo();
    *next_write = std::move(*client_response);
    outgoing_ogw_responses_->updateWriteIndex();

    auto sendMarketUpdate(const MEClientResponse *client_response) noexcept {
      logger_.log("%:% %() % Sending %\n", __FILE__, __LINE__, __FUNCTION__,
                  Common::getCurrentTimeStr(&time_str_),
                  client_response->toString());
      auto next_write = outgoing_ogw_responses_->getNextToWriteTo();
      *next_write = *market_update;

      outgoing_md_updates_->updateWriteIndex();
    }

    auto run() noexcept {
      logger_.log("% :% % () %\n", __FILE__, __LINE__, __FUNCTION__,
                  Common::getCurrentTimeStr(&time_str_t));
      while (run_) {
        const auto me_client_request = incoming_requests_->getNextToread();
        if (LIKELY(me_client_request)) {
          logger_.log("%:% %() % Processing %\n", __FILE__, __LINE__,
                      __FUNCTION__, Common::getCurrentTimeStr(&time_str_),
                      me_client_request->toString());

          processClientRequest(me_client_request);
          incoming_requests_->updateReadIndex();
        }
      }
    }

    MatchingEngine() = delete;
    MatchingEngine(const MatchEngine &) = delete;
    MatchtingEngine &operator=(const MatchingEngine &) = delete;
    MatchingEngine &operator=(const MatchingEngine &&) = delete;

  private:
    OrderBookHashMap ticker_order_;
    ClientRequestLFQueue *incoming_requests_ = nullptr;
    ClientResponeLFQueue *outgoing_ogw_responses_ = nullptr;
    MEMarketUpdateLFQueue *outgoing_md_updates_ = nullptr;

    volatile vool run_ = false;

    std::string time_str;
    Logger logger_;
  };
}
