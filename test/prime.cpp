/**
 * prime.cpp
 *
 * @Author : lostprobe
 * @Date   : 2022/10/22 16:38
 * @Brief  : prime.cpp
 */
#include "util/Timer.hpp"
#include <iostream>
#include <cmath>

static int global_c = 0;

bool is_prime1(int n)
{
    for(int i = 2; i < n; i++)
    {
        if(n % i == 0)
            return false;
    }
    return true;
}

bool is_prime2(int n)
{
    for(int i = 2; i <= (int)sqrt(n); i++)
    {
        if(n % i == 0)
            return false;
    }
    return true;
}

bool is_prime3(int n)
{
    int bound = sqrt(n);
    for(int i = 2; i <= bound; i++)
    {
        if(n % i == 0)
            return false;
    }
    return true;
}

void prime_print(int n)
{
    printf("%d\n", n);
}

void prime_count(int n)
{
    global_c++;
}

void prime_gen(int c, bool (*is_prime)(int n), void (*prime_handler)(int n) = prime_print)
{
    for(int i = 2; i < c; i++)
    {
        if(is_prime(i))
            prime_handler(i);
    }
}

using namespace probe;
int main(int argc, char const *argv[])
{
    Timer timer;

printf("==============\n");
    timer.reset();
    prime_gen(1000, is_prime1, prime_count);
    printf("total found %d\n", global_c);
    printf("%lld us\n", timer.elapsed<Timer::Unit::us>());

    global_c = 0;
    timer.reset();
    prime_gen(1000, is_prime2, prime_count);
    printf("total found %d\n", global_c);
    printf("%lld us\n", timer.elapsed<Timer::Unit::us>());

    global_c = 0;
    timer.reset();
    prime_gen(1000, is_prime3, prime_count);
    printf("total found %d\n", global_c);
    printf("%lld us\n", timer.elapsed<Timer::Unit::us>());
printf("==============\n");

    return 0;
}
