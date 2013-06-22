#ifndef __BOMBER_SERVERv2
#define __BOMBER_SERVERv2

#include "ReceiverContainer.h"
#include "Session.h"

using boost::asio::ip::tcp;

class Server
{
    public:
        Server(boost::asio::io_service& io_service, const tcp::endpoint& endpoint);

        void handleAccept(sessionPtr session, const boost::system::error_code& error);

    private:
        boost::asio::io_service& _ioService;
        tcp::acceptor _acceptor;
        ReceiverContainer _receivers;
};

typedef boost::shared_ptr<Server> serverPtr;

#endif

