#ifndef __BOMBER_CLIENTv2
#define __BOMBER_CLIENTv2

#include "../Common/Message.h"

using boost::asio::ip::tcp;

class Client
{
    public:
        Client(boost::asio::io_service& io_service, tcp::resolver::iterator endpoint_iterator);

        void write(const Message& msg);
        void close();

    private:
        boost::asio::io_service& _ioService;
        tcp::socket _socket;
        Message _readMsg;
        MessageQueue _writeMsgs;
        bool _ready;

        void handleConnect(const boost::system::error_code& error, tcp::resolver::iterator endpoint_iterator);
        void handleReadHeader(const boost::system::error_code& error);
        void handleReadBody(const boost::system::error_code& error);
        void doWrite(Message msg);
        void handleWrite(const boost::system::error_code& error);
        void doClose();
};

#endif

