
#include <iostream>
#include <boost/bind.hpp>

#include "ClientConnection.h"

ClientConnection::ClientConnection(std::string host, std::string port)
{
    tcp::resolver resolver(_ioService);
    tcp::resolver::query query("localhost", "8888"); // TODO: get rid of hardcoded host and port
    tcp::resolver::iterator iterator = resolver.resolve(query);

    _client = new Client(_ioService, iterator);

    _thread = new boost::asio::detail::thread(boost::bind(&boost::asio::io_service::run, &_ioService));
    //boost::asio::detail::thread t(boost::bind(&boost::asio::io_service::run, &ioService));
    //_thread = &t;
}

ClientConnection::~ClientConnection()
{
    _thread->join();
}

void ClientConnection::send(char *cMsg)
{
    Message msg;
    msg.bodyLength(std::strlen(cMsg));
    std::memcpy(msg.body(), cMsg, msg.bodyLength());
    msg.encodeHeader();

    _client->write(msg);
}

void ClientConnection::send(std::vector<unsigned char> msg)
{
    this->send(reinterpret_cast<char*> (&msg[0]));
}
