#pragma once

#include <random>
#include <type_traits>

namespace probe
{
    // T 是整型时启用，包括 bool, char, char16_t, char 32_t, wchar_t
    //                  short, int, long, long long
    template <typename T, typename std::enable_if<std::is_integral_v<T>, T>::type * = nullptr>
    T rand(int64_t seed, T min, T max)
    {
    using namespace std;
        static default_random_engine e(seed);   // 随机数引擎，默认 mt19937
        static uniform_int_distribution<T> u(min, max); // 随机数分布器
        return u(e);
    }

    template <typename T, typename std::enable_if<std::is_integral_v<T>, T>::type * = nullptr>
    T rand(T min, T max)
    {
    using namespace std;
        static default_random_engine e(time(0));
        static uniform_int_distribution<T> u(min, max);
        return u(e);
    }

    // T 是浮点时启用
    template <typename T, typename std::enable_if_t<std::is_floating_point_v<T>, T>* = nullptr>
    T rand(T min, T max)
    {
    using namespace std;
        static default_random_engine e(time(0));
        static uniform_real_distribution<T> u(min, max);
        return u(e);
    }

    template <typename T, typename std::enable_if_t<std::is_floating_point_v<T>, T>* = nullptr>
    T rand(int64_t seed, T min, T max)
    {
    using namespace std;
        static default_random_engine e(time(0));
        static uniform_real_distribution<T> u(min, max);
        return u(e);
    }
}   // namespace probe