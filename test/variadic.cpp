#include <cassert>
#include <utility>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <thread>

static int global_c = 0;

template<typename Func, typename... Args, typename Ret = std::invoke_result_t<Func, Args...>>
auto clock(Func func, Args&&... args) -> Ret
{
    // 检测能否进行 func(args...) 操作
    static_assert(std::is_invocable_v<Func, Args...>, "func must be invoked with args...");

    #define BEGIN auto _begin = std::chrono::steady_clock::now()

    #define END \
        auto diff = std::chrono::steady_clock::now() - _begin; \
        auto c = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count()

    if constexpr (std::is_void_v<Ret>)
    {
        BEGIN;
        func(args...);
        END;
        std::cout << "Elapsed " << c << " ms\n";
    }
    else
    {
        BEGIN;
        auto ret = func(args...);
        END;
        std::cout << "Elapsed " << c << " ms\n";
        return ret;
    }
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
    using namespace std::chrono_literals;
    clock(prime_gen, 1000, is_prime1, prime_count);
    clock(prime_gen, 10000, is_prime1, prime_count);
    clock(prime_gen, 100000, is_prime1, prime_count);
    clock(dosomething);
    // clock(&global_c);
    std::string s = __FUNCTION__;
    std::vector<std::string> v;
    clock([&]() {
        for(int i = 0; i < 0x8000; i++)
            v.emplace_back(s);
    });
    std::cout << clock([]() {
        std::this_thread::sleep_for(100ms);
        return 100;
    }) << std::endl;

    return 0;
}