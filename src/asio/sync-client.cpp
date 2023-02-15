/**
 * sync-client.cpp
 *
 * @author : lostprobe
 * @date   : 2023/02/12 19:13
 * @brief  : sync-client.cpp
 */

#include <iostream>
#include <vector>

#include <boost/asio.hpp>

using namespace boost::asio;
using std::cout, std::endl, std::vector;

int main(int argc, char **argv)
try
{
    io_service io;
    ip::tcp::socket sock(io);
    ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 9000);
    sock.connect(ep);
    cout << sock.available() << endl;
    vector<char> str(sock.available() + 1, 0);
    sock.receive(buffer(str));
    cout << "recive from: " << sock.remote_endpoint().address() << endl;
    cout << &str[0] << endl;
}
catch (std::exception &e)
{
    std::cout << e.what() << std::endl;
}