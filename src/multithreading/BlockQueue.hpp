#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

#include <fmt/core.h>
#include <fmt/color.h>

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
        while(is_full()) {    // 队列满时等待
            _cv_full.wait(lock);
        }
        _q.emplace(e);
        _cv_empty.notify_all();
    }

    int pop()
    {
        std::unique_lock lock(_mtx);
        while(is_empty()) {    // 无数据时等待
            _cv_empty.wait(lock);
        }
        auto ret = _q.front();
        _q.pop();
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