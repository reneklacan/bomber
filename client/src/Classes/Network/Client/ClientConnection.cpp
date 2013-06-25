
#include <iostream>
#include <boost/bind.hpp>

#include "ClientConnection.h"
#include "../Common/ReceiveDelegate.h"

ClientConnection::ClientConnection(std::string host, std::string port)
{
    tcp::resolver resolver(_ioService);
    tcp::resolver::query query(host, port);
    tcp::resolver::iterator iterator = resolver.resolve(query);

    _client = new Client(_ioService, iterator);
    _thread = new boost::asio::detail::thread(boost::bind(&boost::asio::io_service::run, &_ioService));
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

void ClientConnection::addReceiveDelegate(ReceiveDelegate *delegate)
{
    _client->addReceiveDelegate(delegate);
}
