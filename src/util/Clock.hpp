/**
 * Timer.hpp
 *
 * @Author : lostprobe
 * @Date   : 2022/10/22 16:38
 * @Brief  : Timer.hpp
 */
#pragma once

#include <chrono>
#include <ctime>

namespace probe
{

    /// @brief 计时器
    class Clock
    {
        std::chrono::time_point<std::chrono::steady_clock> _begin;

    public:
        /// @brief 定义时间单位的缩写
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
        Clock() : _begin(std::chrono::steady_clock::now())
        {
        }

        /// @brief 重置当前计时器，使其重新开始计时
        void reset()
        {
            _begin = std::chrono::steady_clock::now();
        }

        /// @brief 返回当前耗时
        /// @tparam TimeUnit 要转换到的时间单位，默认使用毫秒(ms)
        /// @return 以模板参数 TimeUnit 描述的时间长度
        template <typename TimeUnit = std::chrono::milliseconds>
        long long elapsed()
        {
            auto timespan = std::chrono::steady_clock::now() - _begin;
            return std::chrono::duration_cast<TimeUnit>(timespan).count();
        }

        /// @brief 一个独立的计时器，输出函数的运行时间
        /// @tparam Func
        /// @tparam ...Args
        /// @param func 要测试的函数
        /// @param ...args 函数的参数列表
        /// @return func 运行的毫秒数
        template <typename Func, typename... Args>
        static long long clock(Func func, Args &&...args)
        {
            // 检测能否进行 func(args...) 操作
            static_assert(std::is_invocable_v<Func, Args...>, "func must be invoked with args...");

            auto _begin = std::chrono::steady_clock::now();

            func(args...);

            auto span = std::chrono::steady_clock::now() - _begin;
            auto c = std::chrono::duration_cast<std::chrono::milliseconds>(span).count();
            std::cout << "Elapsed " << c << " ms\n";
            return c;
        }

    private:
        struct datetime
        {
            int hour, min, sec;
            int year, mon, day;
            int day_in_week;
            int day_in_year;
        };
        static const char *s_wday[7];

    public:
        static struct {
            int year, mon, day;
        } today()
        {
            std::time_t t = std::time(nullptr);
            tm* date = localtime(&t);
            int year = date->tm_year + 1900;
            int mon = date->tm_mon + 1;
            int day = date->tm_mday;
            return {year, mon, day};
        }

        static struct {
            int hour, min, sec;
        } now()
        {
            std::time_t t = std::time(nullptr);
            tm* time = localtime(&t);
            int hour = time->tm_hour;
            int min = time->tm_min;
            int sec = time->tm_sec;
            return {hour, min, sec};
        }
    };
    const char *Clock::s_wday[7] = {
        "SUN",
        "MON",
        "THU",
        "WED",
        "THR",
        "FRI",
        "SAT"
    };
}