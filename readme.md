# cpptest

## 介绍

    一些接口的封装，一些c++技术的实验

    * src/multithreading 多线程相关
    * src/meta-programing STL元编程设施测试
    * src/util 功能性接口
    * src/asio asio相关
    * include 共用头文件

changelog:

    * 2023-6-12 添加changelog

    * 2023-6-8 添加判断可迭代对象的模板
                添加调试宏REPEAT
                添加对值和容器判等的__eq__

    * 2023-4-2 将原本的Timer改为Clock，添加一个Timer

    * 2023-2-15 添加asio实现的客户端和服务端

    * 2022-12-31 添加src/multithreading/co_fib.cpp

    * 2022-11-9 添加计时函数src/util/Timer.hpp::clock

    * 2022-11-5 添加阻塞队列multithreading/BlockQueue
                添加阻塞队列实现的生产者消费者

    * 添加std::asyc示例
    * 添加rand
    * 添加生产者消费者