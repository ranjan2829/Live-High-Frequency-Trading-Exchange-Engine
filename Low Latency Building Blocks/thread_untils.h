#pragma once
#include <iostream>
#include <atomic>
#include <thread>
#include <unistd.h
#include <sys/syscall.h

namespace Common{
    //set affinity for current thread to be placed to the provided core id;
    inline auto setThreadCore(int core_id) noexcept {
        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        CPU_SET(core_id,&cpuset);
        return (pthread_setaffinity_np(pthread_self(),sizeof(cpu_set_t),&cpuset)==0 );


    }
}