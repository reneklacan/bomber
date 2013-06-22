
#include <iostream>
#include "Session.h"

Session::Session(boost::asio::io_service& io_service, ReceiverContainer& receivers)
:_socket(io_service)
,_receivers(receivers)
{
}

tcp::socket& Session::socket()
{
    return _socket;
}

void Session::start()
{
    _receivers.add(shared_from_this());
    boost::asio::async_read(
            _socket,
            boost::asio::buffer(_readMsg.data(), Message::headerLength),
            boost::bind(
                &Session::handleReadHeader,
                shared_from_this(),
                boost::asio::placeholders::error
            )
    );
}

void Session::dispatch(const Message& msg)
{
    std::cout.write(msg.body(), msg.bodyLength());
    std::cout << "\n";

    for (ReceiveDelegate *delegate : _receiveDelegates)
    {
        delegate->receiveServerData(msg.body());
    }

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
                    &Session::handleWrite,
                    shared_from_this(),
                    boost::asio::placeholders::error
                )
        );
    }
}

void Session::handleReadHeader(const boost::system::error_code& error)
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
                    &Session::handleReadBody,
                    shared_from_this(),
                    boost::asio::placeholders::error
                )
        );
    }
    else
    {
        _receivers.remove(shared_from_this());
    }
}

void Session::handleReadBody(const boost::system::error_code& error)
{
    if (!error)
    {
        _receivers.dispatch(_readMsg);
        boost::asio::async_read(
                _socket,
                boost::asio::buffer(
                    _readMsg.data(),
                    Message::headerLength
                ),
                boost::bind(
                    &Session::handleReadHeader,
                    shared_from_this(),
                    boost::asio::placeholders::error
                )
        );
    }
    else
    {
        _receivers.remove(shared_from_this());
    }
}

void Session::handleWrite(const boost::system::error_code& error)
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
                        &Session::handleWrite,
                        shared_from_this(),
                        boost::asio::placeholders::error
                    )
            );
        }
    }
    else
    {
        _receivers.remove(shared_from_this());
    }
}

void Session::addReceiveDelegate(ReceiveDelegate *delegate)
{
    _receiveDelegates.insert(delegate);
}
