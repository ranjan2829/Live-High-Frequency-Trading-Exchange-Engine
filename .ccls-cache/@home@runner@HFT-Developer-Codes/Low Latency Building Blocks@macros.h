#pragma once

#include <iostream>
#include <string>
#include <cstdlib>

#define LIKELY(x) __builtin_expect(!!(x), 1)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)

void ASSERT(bool cond, const std::string &msg) {
    if (!cond) {
        std::cerr << msg << std::endl;
        std::abort();
    }
}

void FATAL(const std::string &msg) {
    std::cerr << "FATAL : " << msg << std::endl;
    exit(EXIT_FAILURE);
}
