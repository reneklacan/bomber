
#include "ServerConnection.h"

ServerConnection::ServerConnection(int port)
{
    tcp::endpoint endpoint(tcp::v4(), 8888); //TODO hardcoded port
    _server = new Server(_ioService, endpoint);
    _thread = new boost::asio::detail::thread(boost::bind(&boost::asio::io_service::run, &_ioService));
}

ServerConnection::~ServerConnection()
{
    _thread->join();
}

void ServerConnection::dispatch(char *cMsg)
{
    Message msg;
    msg.bodyLength(std::strlen(cMsg));
    std::memcpy(msg.body(), cMsg, msg.bodyLength());
    msg.encodeHeader();

    _server->getReceiverContainer().dispatch(msg);
}

void ServerConnection::dispatch(std::vector<unsigned char> msg)
{
    this->dispatch(reinterpret_cast<char*> (&msg[0]));
}

void ServerConnection::addReceiveDelegate(ReceiveDelegate *delegate)
{
    _server->getReceiverContainer().addReceiveDelegate(delegate);
}
