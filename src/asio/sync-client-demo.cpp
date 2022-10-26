#include "common.h"
#include <iostream>
#include <vector>
#include <string>

using namespace boost::asio;

int main()
{
    try
    {
        io_service service;
        ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 9000);
        ip::tcp::socket sock(service);
        boost::system::error_code ec;
        sock.connect(ep, ec);

        fmt::print("socket.available: {}\n", sock.available());

        std::string data(32, 0);
        // std::vector<char> data(sock.available() + 1, 0);
        while(true)
        {
            sock.receive(buffer(data));
            fmt::print("received: {}\n", data);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}