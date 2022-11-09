#include <cassert>
#include <utility>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

static int global_c = 0;

template<typename Func, typename... Args>
long long clock(Func func, Args&&... args)
{
    // 检测能否进行 func(args...) 操作
    static_assert(std::is_invocable_v<Func, Args...>, "func must be invoked with args...");

    auto _begin = std::chrono::steady_clock::now();

    func(args...);

    auto span = std::chrono::steady_clock::now() - _begin;
    auto c = std::chrono::duration_cast<std::chrono::milliseconds>(span).count();
    std::cout << "Elapsed " << std::chrono::duration_cast<std::chrono::milliseconds>(span).count() << " ms\n";
    return c;
}

void dosomething()
{
    std::cout << "do something\n";
}

inline void prime_count(int n)
{
    global_c++;
}

bool is_prime1(int n)
{
    for(int i = 2; i < n; i++)
    {
        if(n % i == 0)
            return false;
    }
    return true;
}

void prime_gen(int c, bool (*is_prime)(int n), void (*prime_handler)(int n) = prime_count)
{
    for(int i = 2; i < c; i++)
    {
        if(is_prime(i))
            prime_handler(i);
    }
}

int main()
{
    // clock(prime_gen, 1000, is_prime1, prime_count);
    // clock(prime_gen, 10000, is_prime1, prime_count);
    // clock(prime_gen, 100000, is_prime1, prime_count);
    // clock(dosomething);
    // clock(&global_c);
    std::string s = __FUNCTION__;
    std::vector<std::string> v;
    clock([&]() {
        for(int i = 0; i < 0x8000; i++)
            v.emplace_back(s);
    });

    return 0;
}