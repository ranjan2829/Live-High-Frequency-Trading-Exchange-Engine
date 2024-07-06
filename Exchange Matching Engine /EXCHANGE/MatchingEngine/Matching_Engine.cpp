#include "Matching_Engine.h"

namespace Exchange {
MatchingEngine::MatchingEngine(ClientRequestLFQueue *client_requests,
                               ClientResponseLFQueue *client_responses_,
                               MEMarketUpdateLFQueue *market_updates)
    : incoming_requests_(client_requests),
      outgoing_ogw_responses_(client_responses_),
      outgoing_md_updates_(market_updates),
      logger_("exchange_matching_engine.log") {
  for (size_t i = 0; i < ticker_order_book_.size(); ++i) {
    ticker_order_book_[i] = new MEOrderBook(i, &logger_, this);
  }
}
} // namespace Exchange
