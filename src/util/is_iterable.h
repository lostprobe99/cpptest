/**
 * is_iterable.h
 *
 * @author : lostprobe
 * @date   : 2023/05/13 22:47
 * @brief  : is_iterable.h
 */

#include <type_traits>

// 检查类型T是否为可迭代对象
template<typename T, typename = void>
struct is_iterable : std::false_type {};

template<typename T>
struct is_iterable<T,
    std::void_t<decltype(std::begin(std::declval<T>())),
               decltype(std::end(std::declval<T>()))>>
    : std::true_type {};

template<typename T>
inline constexpr bool is_iterable_v = is_iterable<T>::value;
