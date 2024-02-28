#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include "Disruptor.h" // Example Disruptor library

// Define a market data event structure
struct MarketDataEvent {
    std::string symbol;
    double price;
    std::chrono::steady_clock::time_point timestamp;
    // Other relevant data fields
};

// Define a handler for processing market data events
class MarketDataEventHandler {
public:
    void onEvent(const MarketDataEvent& event) {
        // Process market data event
        std::cout << "Received market data: Symbol=" << event.symbol << ", Price=" << event.price << std::endl;
        // Perform trading decisions, order execution, etc.
    }
};

// Define a disruptor ring buffer for market data events
using MarketDataDisruptor = Disruptor<MarketDataEvent>;

// Function to simulate market data generation
void generateMarketData(MarketDataDisruptor& disruptor) {
    // Simulate receiving market data from sources
    while (true) {
        MarketDataEvent event;
        event.symbol = "AAPL";
        event.price = 150.25; // Simulated price
        event.timestamp = std::chrono::steady_clock::now();
        disruptor.publish(event); // Publish market data event to the disruptor
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate data arrival interval
    }
}

int main() {
    // Create a Disruptor instance with a buffer size of 1024 and a single handler
    MarketDataDisruptor marketDataDisruptor(1024);
    MarketDataEventHandler marketDataHandler;
    marketDataDisruptor.handleEventsWith(&marketDataHandler);

    // Create worker threads to process market data events
    std::vector<std::thread> workerThreads;
    for (int i = 0; i < std::thread::hardware_concurrency(); ++i) {
        workerThreads.emplace_back([&] {
            marketDataDisruptor.run(); // Start the disruptor event loop
        });
    }

    // Start a thread to generate simulated market data
    std::thread marketDataGenerator(generateMarketData, std::ref(marketDataDisruptor));

    // Wait for the market data generator thread to finish (which never happens in this example)
    marketDataGenerator.join();

    // Stop the disruptor event loop in each worker thread
    for (auto& thread : workerThreads) {
        marketDataDisruptor.halt();
        thread.join();
    }

    return 0;
}
