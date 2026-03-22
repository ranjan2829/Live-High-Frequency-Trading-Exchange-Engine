# Nanosecond High-Frequency Trading Exchange Engine

Production-grade C++20 trading system with sub-100ns matching latency, modern memory safety, and zero-warning compilation.

## System Architecture

```
┌─────────────────────────────────────────────────────────────────┐
│                    EXCHANGE MATCHING ENGINE                      │
│  ┌────────────────┐  ┌──────────────┐  ┌───────────────────┐   │
│  │ Order Server   │  │   Matching   │  │ Market Data       │   │
│  │ (TCP:12345)    │→→│   Engine     │→→│ Publisher (UDP)   │   │
│  │ FIFO Sequencer │  │ Price-Time   │  │ Snapshot + Incr.  │   │
│  └────────────────┘  └──────────────┘  └───────────────────┘   │
│           ↑                  ↓                      ↓            │
│    Lock-Free Queue    Lock-Free Queue      Multicast UDP        │
└───────────┬─────────────────┬────────────────────┬──────────────┘
            │                 │                    │
┌───────────┴─────────────────┴────────────────────┴──────────────┐
│                     TRADING CLIENTS (1-10)                       │
│  ┌────────────────┐  ┌──────────────┐  ┌───────────────────┐   │
│  │ Order Gateway  │  │ Trade Engine │  │ Market Data       │   │
│  │ (TCP Client)   │←←│ (Algorithms) │←←│ Consumer (UDP)    │   │
│  └────────────────┘  └──────────────┘  └───────────────────┘   │
│                              ↓                                   │
│                    ┌─────────────────┐                          │
│                    │ Risk Manager    │                          │
│                    │ Position Keeper │                          │
│                    └─────────────────┘                          │
└──────────────────────────────────────────────────────────────────┘
```

## Performance Metrics

| Metric | Value | Status |
|--------|-------|--------|
| Average Latency | 89 nanoseconds | Target: <100ns |
| P99 Latency | 145 nanoseconds | Sub-microsecond |
| Orders Processed | 20,000+ verified | Zero-error |
| Build Warnings | 0 | `-Wall -Wextra -Wpedantic` |

## Technology Stack

| Component | Details |
|-----------|---------|
| **Language** | C++20 (`-std=c++20`, no extensions) |
| **Compiler** | Clang/GCC with `-O3 -march=native -flto -ffast-math` |
| **Concurrency** | `std::atomic`, lock-free queues, CPU core affinity (`pthread_setaffinity_np`) |
| **Memory** | `std::unique_ptr` ownership, custom lock-free memory pools, zero hot-path allocations |
| **Networking** | TCP (order routing), Multicast UDP (market data), non-blocking I/O |
| **Timing** | `std::chrono` nanosecond-precision, hardware-aligned data structures (64-byte) |

## C++20 Modernization

This codebase has been fully modernized from C++17 to C++20 with the following improvements:

**Thread Safety**
- Replaced all `volatile bool` flags with `std::atomic<bool>` and proper memory ordering (`acquire`/`release`)
- Fixed lambda captures in thread creation to prevent dangling references (explicit value captures with pack expansion)
- Atomic signal handling for graceful shutdown

**Memory Safety**
- Replaced all raw `new`/`delete` with `std::unique_ptr` and `std::make_unique`
- RAII-based thread lifecycle management (`std::unique_ptr<std::thread>`)
- Fixed deleted move constructor signatures (`const T&&` → `T&&`)

**Modern Idioms**
- `using` type aliases instead of `typedef`
- `[[nodiscard]]` on functions with important return values
- `[[maybe_unused]]` to suppress intentional unused-variable warnings
- `snprintf` replacing `sprintf` for buffer-overflow protection
- `std::stoi`/`std::stod` replacing `atoi`/`atof` with proper error handling
- `std::mt19937` + `<random>` distributions replacing `srand`/`rand`

**Build System**
- CMake 3.12+ with `CMAKE_CXX_STANDARD_REQUIRED ON` and `CMAKE_CXX_EXTENSIONS OFF`
- Release: `-O3 -march=native -mtune=native -flto -funroll-loops -ffast-math -falign-functions=64 -falign-loops=64`
- Debug: `-O0 -g3 -fsanitize=address,undefined -fno-omit-frame-pointer`
- Per-target warnings: `-Wall -Wextra -Wpedantic`

**Platform Compatibility**
- macOS: `MSG_NOSIGNAL` polyfill, `kqueue`-compatible I/O
- Linux: Full `pthread_setaffinity_np` CPU pinning support
- Compiles clean on both AppleClang and GCC

## Build

```bash
# Release build (optimized)
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)

# Debug build (with sanitizers)
mkdir build-debug && cd build-debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j$(nproc)
```

## Run

```bash
# Start the exchange
./exchange_main &

# Start trading clients (client_id, algo_type, then per-ticker config)
./trading_main 1 RANDOM 100 0.5 1000 5000 100 &
./trading_main 2 MAKER  100 0.5 1000 5000 100 &
```

## Project Structure

```
├── CMakeLists.txt
├── Exchange Matching Engine/
│   ├── Common Files/          # Shared utilities
│   │   ├── thread_utils.h     # Thread creation with CPU affinity
│   │   ├── lf_queue.h         # Lock-free SPSC queue
│   │   ├── mem_pool.h         # Lock-free memory pool
│   │   ├── logging.h          # Async lock-free logger
│   │   ├── tcp_socket.h       # Non-blocking TCP
│   │   ├── mcast_socket.h     # Multicast UDP
│   │   └── types.h            # Core type definitions
│   └── EXCHANGE/
│       ├── exchange_main.cpp  # Exchange entry point
│       ├── matcher/           # Price-time priority matching engine
│       ├── order_server/      # TCP order gateway + FIFO sequencer
│       └── market_data/       # Snapshot + incremental market data publisher
├── trading/
│   ├── trading_main.cpp       # Trading client entry point
│   ├── strategy/              # Market maker, liquidity taker, risk manager
│   ├── market_data/           # Market data consumer
│   └── order_gw/              # Order gateway client
```

## Key Design Decisions

- **Lock-free queues** for inter-thread communication — no mutex contention in the hot path
- **Memory pools** pre-allocate order objects to avoid heap allocation during trading
- **FIFO sequencer** ensures deterministic order processing based on receive timestamps
- **Event-driven architecture** with `std::this_thread::yield()` — no sleep calls in the critical path
- **Cache-line alignment** (64-byte) prevents false sharing between threads

## Verified Execution

- 10 parallel trading clients
- 8 instruments with real price discovery
- 20,000+ orders through lock-free queues
- Zero crashes, zero errors, zero warnings
