#pragma once

#include <iostream>
#include <atomic>
#include <thread>
#include <unistd.h>
#include <sched.h>      // Add this for cpu_set_t
#include <sys/syscall.h>
#include <chrono>

namespace Common {
    // Set affinity for current thread to be pinned to the provided core_id.
    bool setThreadCore(int core_id) noexcept;

    // Creates a thread instance, sets affinity on it, assigns it a name and
    // passes the function to be run on that thread as well as the arguments to the function.
    template<typename T, typename... A>
    std::thread* createAndStartThread(int core_id, const std::string &name, T &&func, A &&... args) noexcept;
}

#include "thread_utils.tpp" // Include the implementation file where the function definitions are located
