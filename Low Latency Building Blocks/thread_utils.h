// thread_utils.h
#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include <string>

namespace Common {
    // Empty implementation for setThreadCore
    inline bool setThreadCore(int core_id) noexcept {
        // No actual implementation, returns true by default
        return true;
    }

    template<typename T, typename... A>
    inline auto createAndStartThread(int core_id, const std::string &name, T &&func, A &&... args) noexcept {
        auto t = new std::thread([&]() {
            if (core_id >= 0 && !setThreadCore(core_id)) {
                std::cerr << "Failed to set core affinity for " << name << std::endl;
                exit(EXIT_FAILURE);
            }
            std::cout << "Set core affinity for " << name << std::endl;

            std::forward<T>(func)((std::forward<A>(args))...);
        });

        using namespace std::literals::chrono_literals;
        std::this_thread::sleep_for(1s);

        return t;
    }
}
