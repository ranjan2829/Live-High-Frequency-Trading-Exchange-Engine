cmake_minimum_required(VERSION 3.27)
project(HFT_Developer_Codes)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(HFT_Developer_Codes
        sample.cpp
        main.h
        "Low Latency Building Blocks/macros.h"
        "Low Latency Building Blocks/main.cpp")
