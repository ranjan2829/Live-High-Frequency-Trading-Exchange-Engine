#pragma once
#include <string>
#include <fstream>
#include <cstdio>
#include "macros.h"
#include "LockFreeQueues.h"
#include "thread_utils.h"
#include "time_utils.h"
namespace Common{
    constexpr size_t LOQ_QUEUE_SIZE=8*1024*1024;
    enum class LogType : int8_t{
        CHAR = 0,
        INTEGER = 1,
        LONG_INTEGER = 2,
        LONG_LONG_INTEGER = 3,
        UNSIGNED_INTEGER = 4,
        UNSIGNED_LONG_INTEGER = 5,
        UNSIGNED_LONG_LONG_INTEGER = 6,
        FLOAT = 7,
        DOUBLE = 8

    };
    struct LogElement{
        LogType type_=LogType::CHAR;
        union{
            char x;
            int i;
            long l;
            long long ll;
            unsigned u;
            unsigned long ul;
            unsignec long long ull;
            float f;
            double d;

        }u_;

        
    };
    class Logger final{
        public:
        auto flushQueue() noexcept{
            while(running_){

            }
        }
        private:
        const std::string file_name;
        std::ofstream file_;
        LFQueue<LogElement> queue_;
        std::atomic<bool> running_={true};
        std::thread *logger_thread=nullptr;

    };


 }



    

