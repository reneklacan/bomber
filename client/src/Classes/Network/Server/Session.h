#ifndef __BOMBER_SESSION
#define __BOMBER_SESSION

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>

#include "Receiver.h"
#include "ReceiverContainer.h"

using boost::asio::ip::tcp;

class Session : public Receiver, public boost::enable_shared_from_this<Session>
{
    public:
        Session(boost::asio::io_service& io_service, ReceiverContainer& receivers);

        tcp::socket& socket();
        void start();
        void dispatch(const Message& msg);
        void handleReadHeader(const boost::system::error_code& error);
        void handleReadBody(const boost::system::error_code& error);
        void handleWrite(const boost::system::error_code& error);

    private:
        tcp::socket _socket;
        ReceiverContainer& _receivers;
        Message _readMsg;
        MessageQueue _writeMsgs;
};

typedef boost::shared_ptr<Session> sessionPtr;

#endif

