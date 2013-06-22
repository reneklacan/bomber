#ifndef __BOMBER_CLIENTv2_CONNECTION
#define __BOMBER_CLIENTv2_CONNECTION

#include <vector>
#include <boost/asio.hpp>

#include "Client.h"

class ClientConnection
{
    public:
        ClientConnection(std::string host, std::string port);
        ~ClientConnection();

        void send(char *msg);
        void send(std::vector<unsigned char> msg);
        void addReceiveDelegate(ReceiveDelegate *delegate);
    private:
        boost::asio::io_service _ioService;
        Client *_client;
        boost::asio::detail::thread *_thread;
};

#endif

