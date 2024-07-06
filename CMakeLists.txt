cmake_minimum_required(VERSION 3.10)  # Set a valid minimum required version

project(HFT_Developer_Codes)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(HFT_Developer_Codes


        "macros.h"
        "main.cpp"
        "thread_utils.h"
        "thread.cpp"
        "memory_pool.h"
        "logging.h"
        "logger.cpp"
        "Exchange Matching Engine /EXCHANGE/Order-Server/client_response.h"
        "Exchange Matching Engine /EXCHANGE/Market-Update/market_update.h"
        "Exchange Matching Engine /EXCHANGE/MatchingEngine/ME_order.h"
        "Exchange Matching Engine /EXCHANGE/MatchingEngine/Matching_Engine.h"
        "Exchange Matching Engine /EXCHANGE/MatchingEngine/me_order_book.h"
        "Exchange Matching Engine /EXCHANGE/MatchingEngine/MatchingEngine.cpp")
