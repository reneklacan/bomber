/*
 * Project: Bomber
 * Created: 18.06.2013
 * Class: Sockets
 */

#ifndef __BOMBER_SOCKET_LAYER
#define __BOMBER_SOCKET_LAYER

#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>

#include "../Server/Logic.h"
#include "../Server/Sender.h"

using boost::asio::ip::tcp;

class tcp_connection : public boost::enable_shared_from_this<tcp_connection>
{
public:
  typedef boost::shared_ptr<tcp_connection> pointer;

  static pointer create(boost::asio::io_service& io_service)
  {
    return pointer(new tcp_connection(io_service));
  }

  tcp::socket& socket();

  void start();

private:
  tcp_connection(boost::asio::io_service& io_service) : socket_(io_service) {}

  void handle_write(const boost::system::error_code&, size_t /*bytes_transferred*/) {}

  tcp::socket socket_;
  std::string message_;
};


class tcp_server
{
public:
  tcp_server(boost::asio::io_service& io_service, Logic* logic)
    : acceptor_(io_service, tcp::endpoint(tcp::v4(), 2244)), _logic(logic)
  {
    start_accept();
  }

private:
  void start_accept();

  void handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code& error);

  tcp::acceptor acceptor_;
  Logic* _logic;
};

class TcpClient
{
public:
  void sendData(std::string ip, std::string port, std::vector<unsigned char> data);
  std::vector<unsigned char> *receiveData(std::string ip, std::string port);

private:
  std::vector<unsigned char> _buf;
};

class tcp_connection_sync : public boost::enable_shared_from_this<tcp_connection_sync>
{
public:
  typedef boost::shared_ptr<tcp_connection_sync> pointer;

  static pointer create(boost::asio::io_service& io_service)
  {
    return pointer(new tcp_connection_sync(io_service));
  }

  tcp::socket& socket();

  void start();

private:
  tcp_connection_sync(boost::asio::io_service& io_service) : socket_(io_service) {}

  void handle_write(const boost::system::error_code&, size_t /*bytes_transferred*/) {}

  tcp::socket socket_;
  std::vector<unsigned char> message_;
};


class tcp_server_sync
{
public:
  tcp_server_sync(boost::asio::io_service& io_service, Sender* sender)
    : acceptor_(io_service, tcp::endpoint(tcp::v4(), 2245)), _sender(sender)
  {
    start_accept();
  }

private:
  void start_accept();

  void handle_accept(tcp_connection_sync::pointer new_connection, const boost::system::error_code& error);

  tcp::acceptor acceptor_;
  Sender* _sender;
};

#endif