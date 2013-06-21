/*
 * Project: Bomber
 * Created: 18.06.2013
 * Class: Sockets
 */

#include "Sockets.h"

std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}


tcp::socket& tcp_connection::socket()
{
  return socket_;
}

void tcp_connection::start(Logic *logic)
{
  message_ = logic->getState();

  boost::asio::async_write(socket_, boost::asio::buffer(message_),
      boost::bind(&tcp_connection::handle_write, shared_from_this(),
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

void tcp_server::start_accept()
{
  tcp_connection::pointer new_connection =
    tcp_connection::create(acceptor_.get_io_service());

  acceptor_.async_accept(new_connection->socket(),
      boost::bind(&tcp_server::handle_accept, this, new_connection,
        boost::asio::placeholders::error));
}

void tcp_server::handle_accept(tcp_connection::pointer new_connection,
    const boost::system::error_code& error)
{
  if (!error)
  {
    // Receive data
    boost::array<char, 9> buf;
    boost::system::error_code error;

    size_t len = new_connection->socket().read_some(boost::asio::buffer(buf), error);

    // Connection closed by peer
    if (error == boost::asio::error::eof)
      ;
    // Other error
    else if (error)
      throw boost::system::system_error(error);

    // Send data to Logic only if there are some
    if(len > 1) 
    {
      //Convert to vector and send data to Logic
      std::vector<unsigned char> vData(buf.begin(), buf.end());
      _logic->updateState(vData);
    }

    new_connection->start(_logic);
  }

  start_accept();
}


void TcpClient::sendData(std::string ip, std::string port, std::vector<unsigned char> data)
{
  try
  {
    boost::asio::io_service io_service;

    tcp::resolver resolver(io_service);
    tcp::resolver::query query(ip, port);
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    tcp::socket socket(io_service);
    boost::asio::connect(socket, endpoint_iterator);

    boost::asio::write(socket, boost::asio::buffer(data));

    socket.close();
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}


std::vector<unsigned char> *TcpClient::receiveData(std::string ip, std::string port)
{
  try
  {
    boost::asio::io_service io_service;

    tcp::resolver resolver(io_service);
    tcp::resolver::query query(ip, port);
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    tcp::socket socket(io_service);
    boost::asio::connect(socket, endpoint_iterator);

    boost::asio::write(socket, boost::asio::buffer(""));

    // Receive data
    boost::array<char, 128> buf;
    boost::system::error_code error;

    size_t len = socket.read_some(boost::asio::buffer(buf), error);
    for(unsigned int i = 0; i < len; i++)
    {
      _buf.push_back(buf[i]);
    }

    // Connection closed by peer
    if (error == boost::asio::error::eof)
      ;
    // Other error
    else if (error)
      throw boost::system::system_error(error);

    //std::cout.write(buf.data(), len);
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return &_buf;
}