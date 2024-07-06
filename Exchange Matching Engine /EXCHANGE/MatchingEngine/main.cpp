// main.cpp
#include "Matching_Engine.h"

int main() {
    // Initialize necessary queues
    ClientRequestLFQueue client_requests;
    ClientResponseLFQueue client_responses;
    MEMarketUpdateLFQueue market_updates;

    // Create an instance of MatchingEngine
    Exchange::MatchingEngine engine(&client_requests, &client_responses, &market_updates);

    // Start the engine
    engine.start();

    // Stop the engine
    engine.stop();

    return 0;
}
