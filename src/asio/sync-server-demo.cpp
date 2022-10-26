#include "common.h"
#include <iostream>
#include <memory>
#include <thread>
#include <future>
#include <chrono>

using namespace boost::asio;

using socket_ptr = std::shared_ptr<ip::tcp::socket>;

void client_session(socket_ptr sock)
{
    while (true)
    {
        char data[512];
        size_t len = sock->read_some(buffer(data));
        if (len > 0)
            write(*sock, buffer("ok", 2));
        if (!sock->available())
            return;
    }
}

void client_session(ip::tcp::socket &sock)
{
    using namespace std::chrono_literals;
    while (true)
    {
        // char data[512];
        // size_t len = sock.receive(buffer(data));
        // if(len > 0)
        //     fmt::print(fmt::fg(fmt::color::yellow), "receive: {}\n", data);
        sock.send(buffer("ok"));
        std::this_thread::sleep_for(1s);
    }
}

int main(int argc, char const *argv[])
{
    try
    {
        io_service service;
        ip::tcp::endpoint ep(ip::tcp::v4(), 9000);
        ip::tcp::acceptor ac(service, ep);
        int c = 1;
        while (true)
        {
            // socket_ptr sock(new ip::tcp::socket(service));
            ip::tcp::socket sock(service);
            fmt::print("waiting for connection...\n");
            // ac.accept(*sock);
            ac.accept(sock);
            fmt::print(fmt::fg(fmt::color::green), "client [{}]: {}\n", c++, sock.remote_endpoint().address().to_string());
            std::thread([&]()
                        { client_session(sock); })
                .join();
            // sock.send(buffer("ok"));
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}