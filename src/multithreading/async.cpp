/**
 * async.cpp
 *
 * @Author : lostprobe
 * @Date   : 2022/08/23 16:59
 * @Brief  : async.cpp
 */

#include <iostream>
#include <thread>
#include <future>
#include <string>
#include <chrono>

#include <fmt/core.h>
#include <fmt/printf.h>

int download(std::string file)
{
    using namespace std::chrono_literals;
    for (int i = 0; i < 10; i++)
    {
        // printf("Downloading %s (%d%)...\n", file.c_str(), i * 10);
        fmt::print("Downloading {} ({}%)...\n", file, i * 10);
        std::this_thread::sleep_for(400ms);
    }
    // std::cout << "Download complete: " << file << std::endl;
    fmt::print("Download complete: {}\n", file);
    return 404;
}

void interact()
{
    std::string name;
    std::cin >> name;
    std::cout << "Hi: " << name << std::endl;
}

int main()
{
    std::future<int> fret = std::async(
        [&] {
            return download("Hello.zip");
        }
    );

    interact();

    int ret = fret.get();
    fmt::print("Download result: {}", ret);

    return 0;
}