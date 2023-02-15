/**
 * sync-server.cpp
 *
 * @author : lostprobe
 * @date   : 2023/02/12 19:13
 * @brief  : sync-server.cpp
 */

#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using std::cout, std::endl;

int main(int argc, char ** argv)
try
{
    cout << "server start." << endl;
    io_service io;
    ip::tcp::acceptor ac(io, ip::tcp::endpoint(ip::tcp::v4(), 9000));
    cout << ac.local_endpoint().address() << endl;
    while(1)
    {
        ip::tcp::socket sock(io);
        ac.accept(sock);
        cout << "client: ";
        cout << sock.remote_endpoint().address() << endl;
        sock.send(buffer("hello asio"));
    }
}
catch(std::exception& e)
{
    cout << e.what() << endl;
}