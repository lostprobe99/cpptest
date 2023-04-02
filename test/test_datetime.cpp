#include <iostream>
#include <ctime>
#include <iomanip>
#include <fmt/core.h>
#include "util/Clock.hpp"

using namespace std;

int main()
{
    time_t t = time(nullptr);
    tm* datetime = gmtime(&t);  // UTC + 0
    fmt::print("{}/{}/{} {}:{}:{}\n", datetime->tm_year + 1900,  datetime->tm_mon + 1, datetime->tm_mday,
                                    datetime->tm_hour, datetime->tm_min, datetime->tm_sec);
    datetime = localtime(&t);   // UTC + 8
    fmt::print("{}/{}/{} {}:{}:{}\n", datetime->tm_year + 1900,  datetime->tm_mon + 1, datetime->tm_mday,
                                    datetime->tm_hour, datetime->tm_min, datetime->tm_sec);
    auto [year, mon, day] = probe::Clock::today();
    auto [hour, min, sec] = probe::Clock::now();
    fmt::print("{}/{}/{} {}:{}:{}\n", year, mon, day, hour, min, sec);

    return 0;
}