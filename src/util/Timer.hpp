/**
 * Timer.hpp
 *
 * @Author : lostprobe
 * @Date   : 2022/10/22 16:38
 * @Brief  : Timer.hpp
 */
#pragma once

#include <chrono>

namespace probe
{

    class Timer
    {
        std::chrono::time_point<std::chrono::steady_clock> _begin;
    
    public:
        struct Unit
        {
            using ns = std::chrono::nanoseconds;
            using us = std::chrono::microseconds;
            using ms = std::chrono::milliseconds;
            using s = std::chrono::seconds;
            using min = std::chrono::minutes;
            using h = std::chrono::hours;
        };

    public:
        Timer() : _begin(std::chrono::steady_clock::now())
        {
        }

        void reset()
        {
            _begin = std::chrono::steady_clock::now();
        }

        template <typename TimeUnit = std::chrono::milliseconds>
        long long elapsed()
        {
            auto timespan = std::chrono::steady_clock::now() - _begin;
            return std::chrono::duration_cast<TimeUnit>(timespan).count();
        }
    };
}