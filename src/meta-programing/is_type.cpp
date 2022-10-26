#include <iostream>
#include <type_traits>

#include <fmt/core.h>

using namespace std;

int main()
{
    fmt::print("int    is floating point: {}\n", is_floating_point_v<int>);
    fmt::print("int    is integral_v    : {}\n", is_integral_v<int>);
    fmt::print("double is floating point: {}\n", is_floating_point_v<double>);
    fmt::print("double is integral_v    : {}\n", is_integral_v<double>);
    fmt::print("main   is floating point: {}\n", is_floating_point_v<decltype(&main)>);
    fmt::print("main   is integral_v    : {}\n", is_integral_v<decltype(&main)>);

    return 0;
}