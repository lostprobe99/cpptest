/**
 * Timer.h
 *
 * @author : lostprobe
 * @date   : 2023/03/25 22:27
 * @brief  : 并不精准
 */

#pragma once

#include <functional>
#include <thread>

namespace probe
{
    class Timer
    {
    private:
        /* data */
    public:
        Timer()
        {
        }
        ~Timer()
        {
        }

        // 返回值为 void 时
        template <typename Func, typename... Args, typename Ret = std::invoke_result_t<Func, Args...>,
                  typename std::enable_if_t<std::is_void_v<typename Ret>> * = nullptr>
        static auto timeout(Func func, int ms, Args &&...args) -> Ret
        {
            static_assert(std::is_invocable_v<Func, Args...>, "func must be invoked with args...");
            std::this_thread::sleep_for(std::chrono::milliseconds(ms));
            func(args...);
        }

        // 返回值为非 void 时匹配
        template <typename Func, typename... Args, typename Ret = std::invoke_result_t<Func, Args...>,
                  typename std::enable_if_t<!std::is_void_v<typename Ret>> * = nullptr>
        static auto timeout(Func func, int ms, Args &&...args) -> Ret
        {
            static_assert(std::is_invocable_v<Func, Args...>, "func must be invoked with args...");
            std::this_thread::sleep_for(std::chrono::milliseconds(ms));
            Ret r = func(args...);
            return r;
        }

        template <typename Func, typename... Args>
        static void interval(Func func, int ms, Args &&...args)
        {
            static_assert(std::is_invocable_v<Func, Args...>, "func must be invoked with args...");
            while (1)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(ms));
                func(args...);
            }
        }
    };
} // namespace probe
