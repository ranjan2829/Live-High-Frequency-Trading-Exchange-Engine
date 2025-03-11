# Live High-Frequency Trading Exchange Engine

## Overview
This project is a **high-performance, low-latency exchange engine** designed for High-Frequency Trading (HFT). It provides efficient **order matching**, **real-time market data processing**, and **concurrent trade execution** using optimized C++ code and lock-free data structures.

The engine is built with **multi-threading**, **memory pooling**, and **low-latency networking** to ensure rapid trade execution and seamless order processing. It is suitable for hedge funds, proprietary trading firms, and developers building their own exchange infrastructure.

---

## Features
- **Ultra-low latency order matching** using efficient **lock-free queues**
- **Multi-threaded architecture** for handling high trade volumes
- **Memory pool management** for optimized performance
- **Logging and debugging support** for monitoring exchange activity
- **Modular C++ design** for easy expansion and customization
- **Build system using CMake** for easy compilation

---

## Directory Structure
```
Live-High-Frequency-Trading-Exchange-Engine/  
│── .ccls-cache/                        # Cached files for CCLS (C++ language server)  
│── .idea/                               # JetBrains IDE configuration files  
│── .vscode/                             # VS Code settings and configurations  
│── Exchange Matching Engine/            # Core components of the exchange engine  
│── ExecutablesFile✅/                    # Stores compiled executable files  
│── build/                               # Build output directory  
│── cmake-build-debug/                   # Debug mode build artifacts  
│── cmake-build-release/                 # Release mode build artifacts  
│── CMakeLists.txt                        # CMake configuration for building the project  
│── LockFreeQueue.cpp                     # Implementation of a lock-free queue  
│── LockFreeQueues.h                      # Header file for lock-free queue  
│── SocketApi.h                           # Socket API definitions for networking  
│── logger.cpp                            # Logging implementation  
│── logging.h                             # Logging header file  
│── macros.h                              # Project-wide macro definitions  
│── main.cpp                              # Main entry point of the application  
│── memory_pool.cpp                       # Memory pool implementation  
│── memory_pool.h                         # Memory pool header file  
│── thread.cpp                            # Thread management implementation  
│── thread_utils.h                        # Thread utility functions  
│── thread_utils.tpp                      # Thread-related template definitions  
│── time_utils.h                          # Time utility functions  
```

---

## How the Project Works
### 1. **Order Matching Engine**
The **Exchange Matching Engine** is responsible for:
- Receiving incoming orders (buy/sell)
- Matching them using an **order book**
- Executing trades and updating market data

### 2. **Lock-Free Queues for Low-Latency Processing**
The project uses **lock-free queues** (from `LockFreeQueue.cpp`) to handle large volumes of order data without blocking threads, ensuring maximum throughput.

### 3. **Networking with Socket API**
`SocketApi.h` provides **network communication** functionality, allowing external clients to connect and send trading instructions to the engine.

### 4. **Multi-Threaded Trade Execution**
- Uses `thread_utils.h` for efficient **parallel processing** of orders.
- `memory_pool.cpp` ensures efficient memory allocation for order processing.
- Orders are stored, matched, and executed in real-time.

### 5. **Logging & Debugging Support**
- `logger.cpp` provides **real-time logging** of exchange activity.
- Debugging tools allow monitoring of trade execution performance.

---

## Installation & Setup
### **Prerequisites**
Make sure you have the following installed:
- **C++ Compiler (GCC/Clang/MSVC)**
- **CMake** (Version 3.10 or later)
- **Linux/macOS/Windows** (Linux is recommended for production HFT environments)

### **Build Instructions**
1. Clone the repository:
   ```sh
   git clone https://github.com/ranjan2829/Live-High-Frequency-Trading-Exchange-Engine.git
   cd Live-High-Frequency-Trading-Exchange-Engine
   ```
2. Create a build directory and run CMake:
   ```sh
   mkdir build && cd build
   cmake ..
   make -j4  # Use multiple cores for faster compilation
   ```
3. Run the exchange engine:
   ```sh
   ./exchange_engine
   ```

---

## How to Use
### **Step 1: Start the Matching Engine**
Run the compiled executable:
```sh
./exchange_engine
```
This will start the order-matching process and wait for incoming trading requests.

### **Step 2: Connect via Socket API**
Use a trading client to send orders via `SocketApi.h`. Example request format:
```
BUY 100 AAPL 150.25  
SELL 50 TSLA 200.75  
```

### **Step 3: Monitor Logs**
Check `logger.cpp` for trade execution logs:
```sh
tail -f trade_logs.txt
```

---

## Performance Optimization
- **Memory Pooling** reduces heap allocations.
- **Lock-Free Queues** avoid thread blocking.
- **Efficient Multithreading** enables parallel order processing.

---

## Future Enhancements
- Implement **FIX protocol** for standard trade messaging.
- Add **REST API** for easier integrations.
- Improve **latency profiling** with hardware-based timestamping.

---

## License
This project is **private**. If you are interested in purchasing a license, please contact the owner.

---

## Contact
For any queries or licensing, please contact **Ranjan** at:
- GitHub: [@ranjan2829](https://github.com/ranjan2829)
- Email: [Your Email Here]

---

### 🚀 Happy Trading! 🚀

