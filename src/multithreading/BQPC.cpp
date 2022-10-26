/**
 * BQPC.cpp
 *
 * @Author : lostprobe
 * @Date   : 2022/10/25 19:07
 * @Brief  : 阻塞队列实现的生产消费者
 */
#include "BlockQueue.hpp"
#include "util/Timer.hpp"
#include "util/rand.hpp"

#include <thread>
#include <vector>
#include <mutex>

#include <fmt/core.h>
#include <fmt/std.h>
#include <fmt/color.h>

constexpr int MAX_TASK_NUM = 8, MAX_PRODUCT_NUM = 50;
int c = 0;  // 产品编号
std::mutex _mtx_product;

void producer(BlockQueue& q)
{
    fmt::print("[{}] running\n", __FUNCTION__);
    while(dbg(c < MAX_PRODUCT_NUM))
    {
        std::lock_guard lock(_mtx_product);
        fmt::print(fmt::fg(fmt::terminal_color::bright_green), "[thread {}] produced {}\n", std::this_thread::get_id(), c);
        q.push(c++);
    fmt::print(fmt::fg(fmt::terminal_color::red), "in [{}] task size: {}\n",__FUNCTION__, q.size());
    }
}

void consumer(BlockQueue& q)
{
    fmt::print("[{}] running\n", __FUNCTION__);
    while(dbg(!q.empty()))
    {
        fmt::print(fmt::fg(fmt::terminal_color::red), "in [{}] task size: {}\n",__FUNCTION__, q.size());
        auto x = q.pop();
        fmt::print(fmt::fg(fmt::terminal_color::bright_yellow), "[thread {}] consumed {}\n", std::this_thread::get_id(), x);
    }
}

int main()
{
    std::vector<std::thread> tpool;
    BlockQueue tasks(MAX_TASK_NUM);

    tpool.emplace_back(consumer, std::ref(tasks));
    tpool.emplace_back(producer, std::ref(tasks));
    // tpool.emplace_back(producer, std::ref(tasks));
    // tpool.emplace_back(producer, std::ref(tasks));

    for(auto&& e : tpool)
        e.join();

    return 0;
}