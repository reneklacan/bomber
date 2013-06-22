
#include <cstdlib>
#include <deque>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "Client.h"

Client::Client(boost::asio::io_service& io_service, tcp::resolver::iterator endpoint_iterator)
:_ioService(io_service)
,_socket(io_service)
{
    tcp::endpoint endpoint = *endpoint_iterator;
    _socket.async_connect(
            endpoint,
            boost::bind(
                &Client::handleConnect,
                this,
                boost::asio::placeholders::error,
                ++endpoint_iterator
            )
    );
}

void Client::write(char *cMsg)
{
    Message msg;
    msg.bodyLength(std::strlen(cMsg));
    std::memcpy(msg.body(), cMsg, msg.bodyLength());
    msg.encodeHeader();
    this->write(msg);
}

void Client::write(const Message& msg)
{
    _ioService.post(boost::bind(&Client::doWrite, this, msg));
}

void Client::close()
{
    _ioService.post(boost::bind(&Client::doClose, this));
}

void Client::handleConnect(const boost::system::error_code& error, tcp::resolver::iterator endpoint_iterator)
{
    if (!error)
    {
        boost::asio::async_read(
                _socket,
                boost::asio::buffer(
                    _readMsg.data(),
                    Message::headerLength
                ),
                boost::bind(
                    &Client::handleReadHeader,
                    this,
                    boost::asio::placeholders::error
                )
        );
    }
    else if (endpoint_iterator != tcp::resolver::iterator())
    {
        _socket.close();
        tcp::endpoint endpoint = *endpoint_iterator;
        _socket.async_connect(
                endpoint,
                boost::bind(
                    &Client::handleConnect,
                    this,
                    boost::asio::placeholders::error,
                    ++endpoint_iterator
                )
        );
    }
}

void Client::handleReadHeader(const boost::system::error_code& error)
{
    if (!error && _readMsg.decodeHeader())
    {
        boost::asio::async_read(
                _socket,
                boost::asio::buffer(
                    _readMsg.body(),
                    _readMsg.bodyLength()
                ),
                boost::bind(
                    &Client::handleReadBody,
                    this,
                    boost::asio::placeholders::error
                )
        );
    }
    else
    {
        doClose();
    }
}

void Client::handleReadBody(const boost::system::error_code& error)
{
    if (!error)
    {
        std::cout.write(_readMsg.body(), _readMsg.bodyLength());
        std::cout << "\n";
        boost::asio::async_read(
                _socket,
                boost::asio::buffer(
                    _readMsg.data(),
                    Message::headerLength
                ),
                boost::bind(
                    &Client::handleReadHeader,
                    this,
                    boost::asio::placeholders::error
                )
        );
    }
    else
    {
        doClose();
    }
}

void Client::doWrite(Message msg)
{
    bool writeInProgress = !_writeMsgs.empty();
    _writeMsgs.push_back(msg);

    if (!writeInProgress)
    {
        boost::asio::async_write(
                _socket,
                boost::asio::buffer(
                    _writeMsgs.front().data(),
                    _writeMsgs.front().length()
                ),
                boost::bind(
                    &Client::handleWrite,
                    this,
                    boost::asio::placeholders::error
                )
        );
    }
}

void Client::handleWrite(const boost::system::error_code& error)
{
    if (!error)
    {
        _writeMsgs.pop_front();
        if (!_writeMsgs.empty())
        {
            boost::asio::async_write(
                    _socket,
                    boost::asio::buffer(
                        _writeMsgs.front().data(),
                        _writeMsgs.front().length()
                    ),
                    boost::bind(
                        &Client::handleWrite,
                        this,
                        boost::asio::placeholders::error
                    )
            );
        }
    }
    else
    {
        doClose();
    }
}

void Client::doClose()
{
    _socket.close();
}

void runClient()
{
    try
    {
        boost::asio::io_service ioService;

        tcp::resolver resolver(ioService);
        tcp::resolver::query query("localhost", "8888");
        tcp::resolver::iterator iterator = resolver.resolve(query);

        Client client(ioService, iterator);

        boost::asio::detail::thread t(boost::bind(&boost::asio::io_service::run, &ioService));

        char line[Message::maxBodyLength + 1];
        while (std::cin.getline(line, Message::maxBodyLength + 1))
        {
            Message msg;
            msg.bodyLength(std::strlen(line));
            std::memcpy(msg.body(), line, msg.bodyLength());
            msg.encodeHeader();
            client.write(msg);
        }

        client.close();
        t.join();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

void runClient2()
{
    try
    {
        boost::asio::io_service ioService;

        tcp::resolver resolver(ioService);
        tcp::resolver::query query("localhost", "8888");
        tcp::resolver::iterator iterator = resolver.resolve(query);

        Client client(ioService, iterator);

        boost::asio::detail::thread t(boost::bind(&boost::asio::io_service::run, &ioService));

        //char line[Message::maxBodyLength + 1];
        char *line;
        while (1)
        {
            std::cout << "tu\n";
            line = (char *) "test";
            client.write(line);
            sleep(1);
            continue;
            Message msg;
            msg.bodyLength(std::strlen(line));
            std::memcpy(msg.body(), line, msg.bodyLength());
            msg.encodeHeader();
            client.write(msg);
            sleep(1);
        }

        client.close();
        t.join();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}
