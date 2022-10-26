#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

#include <fmt/core.h>
#include <fmt/color.h>

#include <dbg.h>

class BlockQueue
{
public:
    using size_type = std::queue<int>::size_type;

private:
    std::queue<int> _q;
    mutable std::mutex _mtx;
    std::condition_variable _cv_full, _cv_empty;
    int _capacity;

private:
    bool is_empty() const
    {
        return _q.empty();
    }

    bool is_full() const
    {
        return _q.size() >= _capacity;
    }

public:
    BlockQueue(int capacity) : _capacity(capacity)
    {}

    ~BlockQueue() {}

    void push(const int& e)
    {
        std::unique_lock lock(_mtx);
        while(dbg(is_full())) {    // 队列满时等待
fmt::print(fmt::fg(fmt::terminal_color::red), "[{}:{} ({})] cv_full.wait\n", __FILE__, __LINE__, __FUNCTION__);
            _cv_full.wait(lock);
        }
        dbg(_q.emplace(e));
fmt::print(fmt::fg(fmt::terminal_color::red), "[{}:{} ({})] cv_empty.notify_all\n", __FILE__, __LINE__, __FUNCTION__);
        _cv_empty.notify_all();
    }

    int pop()
    {
        std::unique_lock lock(_mtx);
        while(dbg(is_empty())) {    // 无数据时等待
fmt::print(fmt::fg(fmt::terminal_color::red), "[{}:{} ({})] cv_empty.wait\n", __FILE__, __LINE__, __FUNCTION__);
            _cv_empty.wait(lock);
        }
        auto ret = _q.front();
        _q.pop();
fmt::print(fmt::fg(fmt::terminal_color::red), "[{}:{} ({})] cv_full.notify_all\n", __FILE__, __LINE__, __FUNCTION__);
        _cv_full.notify_all();
        return ret;
    }

    size_type size()
    {
        std::unique_lock lock(_mtx);
        return _q.size();
    }

    bool empty() const
    {
        std::unique_lock lock(_mtx);
        return is_empty();
    }

    bool full() const
    {
        std::unique_lock lock(_mtx);
        return is_full();
    }
};