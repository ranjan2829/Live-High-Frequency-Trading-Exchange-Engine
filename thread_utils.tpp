//
// Created by Ranjan shahaji shitole on 18/02/24.
//

#include "thread_utils.h"

namespace Common {
    bool setThreadCore(int core_id) noexcept {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);
    return (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) == 0);
}

template<typename T, typename... A>
std::thread* createAndStartThread(int core_id, const std::string &name, T &&func, A &&... args) noexcept {
auto t = new std::thread([&]() {
    if (core_id >= 0 && !setThreadCore(core_id)) {
        std::cerr << "Failed to set core affinity for " << name << " " << pthread_self() << " to " << core_id << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cerr << "Set core affinity for " << name << " " << pthread_self() << " to " << core_id << std::endl;

    std::forward<T>(func)((std::forward<A>(args))...);
});

using namespace std::literals::chrono_literals;
std::this_thread::sleep_for(1s);

return t;
}
}
