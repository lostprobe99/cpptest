/**
 * ProducerConsumer.cpp
 *
 * @Author : lostprobe
 * @Date   : 2022/08/23 16:57
 * @Brief  : ProducerConsumer.cpp
 */

#include <thread>
#include <mutex>
#include <queue>
#include <vector>
#include <chrono>   // for chrono_literals support
#include <condition_variable>

#include "util/rand.hpp" // for probe::rand

#include <fmt/core.h>
#include <fmt/std.h>    // for std::thread::id support
#include <fmt/color.h>  // for fmt::fg and fmt::color

std::mutex _mtx_task /* 控制任务队列 */, _mtx_product /* 控制多个生产者同时生产 */;
std::condition_variable cv_producer, cv_consumer;   // 生产者和消费者互相通信
constexpr int MAX_TASK_NUM = 8, MAX_PRODUCT_NUM = 50;
int c = 0;  // 产品编号

void producer(std::queue<int>& tasks)
{
    using namespace std::chrono_literals;
    // while(true)
    while(c < MAX_PRODUCT_NUM)
    {
        while(tasks.size() >= MAX_TASK_NUM)
        {
            std::unique_lock locker(_mtx_task);
            fmt::print("任务队列已满，等待处理...\n");
            cv_consumer.wait(locker);
        }
        if(probe::rand(0, 100) >= 50)
        {
            if(c >= MAX_PRODUCT_NUM)
                break;
            std::lock_guard grd(_mtx_product);  // 处理多个生产者
            fmt::print(fmt::fg(fmt::terminal_color::bright_green), "[thread {}] produced {}\n", std::this_thread::get_id(), c);
            tasks.push(c++);
            fmt::print("[thread {}] next product is {}\n", std::this_thread::get_id(), c);
            cv_producer.notify_one();
        }
        std::this_thread::sleep_for(100ms);
    }
}

void consumer(std::queue<int>& tasks)
{
    using namespace std::chrono_literals;
    while(true)
    {
        while(tasks.empty())
        {
            std::unique_lock locker(_mtx_task);
            fmt::print("任务队列为空，等待任务...\n");
            cv_producer.wait(locker);
        }
        {
            int t = tasks.front();
            fmt::print(fmt::fg(fmt::terminal_color::bright_yellow), "[thread {}] consumed {}\n", std::this_thread::get_id(), t);
            tasks.pop();
            cv_consumer.notify_all();
        }
        std::this_thread::sleep_for(100ms);
    }
}

int main()
{
    std::vector<std::thread> tpool;
    std::queue<int> tasks;

    tpool.emplace_back(producer, std::ref(tasks));
    tpool.emplace_back(producer, std::ref(tasks));
    tpool.emplace_back(producer, std::ref(tasks));
    tpool.emplace_back(consumer, std::ref(tasks));

    for(auto&& e : tpool)
        e.join();

    return 0;
}