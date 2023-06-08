#pragma once

#include <type_traits>
#include <iterator>
#include "util/is_iterable.h"
// #include "debug.h"

namespace probe
{
    // #define assert_eq(left, right)

    template<typename T, typename std::enable_if_t<std::is_scalar_v<T>>* = nullptr>
    bool __eq__(const T& left, const T& right)
    {
        return left == right;
    }

    // T 是容器
    template<typename T, typename std::enable_if_t<is_iterable_v<T>>* = nullptr>
    bool __eq__(const T& left, const T& right)
    {
        if(std::distance(left.begin(), left.end()) != std::distance(right.begin(), right.end()))
            return false;
        auto left_it = left.begin();
        auto right_it = right.begin();
        auto left_end = left.end();
        auto right_end = right.end();
        while(left_it != left_end && right_it != right_end)
        {
            // cout << eval(*left_it) << " " << eval(*right_it) << endl;
            if(*left_it != *right_it)
                return false;
            left_it++;
            right_it++;
        }
        return true;
    }

} // namespace probe
