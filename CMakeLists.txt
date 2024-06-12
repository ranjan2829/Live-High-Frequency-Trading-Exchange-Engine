cmake_minimum_required(VERSION 3.10)  # Set a valid minimum required version

project(HFT_Developer_Codes)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(HFT_Developer_Codes
        sample.cpp
        main.h
        "Low Latency Building Blocks/macros.h"
        "Low Latency Building Blocks/main.cpp"
        "Low Latency Building Blocks/thread_utils.h"
        "Low Latency Building Blocks/thread.cpp"
        "Low Latency Building Blocks/memory_pool.h"
        "Low Latency Building Blocks/logging.h"
        "Low Latency Building Blocks/logger.cpp"
        "Exchange Matching Engine /EXCHANGE/Order-Server/client_response.h")
