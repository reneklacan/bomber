
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <list>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>

#include "Server.h"

Server::Server(boost::asio::io_service& io_service, const tcp::endpoint& endpoint)
:_ioService(io_service)
,_acceptor(io_service, endpoint)
{
    std::cout << "server\n";

    sessionPtr newSession(new Session(_ioService, _receivers));
    _acceptor.async_accept(
            newSession->socket(),
            boost::bind(
                &Server::handleAccept,
                this,
                newSession,
                boost::asio::placeholders::error
            )
    );
}

void Server::handleAccept(sessionPtr session, const boost::system::error_code& error)
{
    std::cout << "handle accept\n";

    if (!error)
    {
        session->start();
        sessionPtr newSession(new Session(_ioService, _receivers));
        _acceptor.async_accept(
                newSession->socket(),
                boost::bind(
                    &Server::handleAccept,
                    this,
                    newSession,
                    boost::asio::placeholders::error
                )
        );
    }
}

void runServer()
{
    boost::asio::io_service ioService;

    tcp::endpoint endpoint(tcp::v4(), 8888);
    serverPtr server(new Server(ioService, endpoint));

    ioService.run();
}
