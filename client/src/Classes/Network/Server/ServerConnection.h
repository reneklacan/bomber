#ifndef __BOMBER_SERVERv2_CONNECTION
#define __BOMBER_SERVERv2_CONNECTION

#include <vector>
#include <boost/asio.hpp>

#include "ReceiveDelegate.h"
#include "Server.h"

class ServerConnection
{
    public:
        ServerConnection(int port);
        ~ServerConnection();

        void dispatch(char *cMsg);
        void dispatch(std::vector<unsigned char> msg);
        void addReceiveDelegate(ReceiveDelegate *delegate);
    private:
        boost::asio::io_service _ioService;
        Server *_server;
        boost::asio::detail::thread *_thread;
};

#endif

