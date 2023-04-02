#include "util/Timer.h"
#include "util/Clock.hpp"
#include <iostream>
#include "fmt/core.h"
#include <chrono>

void f()
{
    std::cout << __FUNCTION__ << std::endl;
}

void g()
{
    static int i = 0;
    std::cout << i++ << ": " << __FUNCTION__ << std::endl;
}

int y(int i)
{
    return i;
}

int main()
{
    probe::Timer timer;
    auto start = std::chrono::steady_clock::now();
    // timer.timeout(f, 2000);
    auto end = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    // fmt::print("{}ms\n", diff.count());
    probe::Clock::clock(probe::Timer::timeout<decltype(f)>, f, 2000);

    start = std::chrono::steady_clock::now();
    int ret = timer.timeout(y, 2000, 10);
    end = std::chrono::steady_clock::now();
    diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    fmt::print("{}ms\n", diff.count());
    fmt::print("y return value: {}\n", ret);

    probe::Timer::interval(g, 2000);

    return 0;
}