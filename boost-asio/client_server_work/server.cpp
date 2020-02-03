#include <cstdlib>
#include <iostream>
#include <thread>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

const int max_length = 1024;

void session(tcp::socket sock)
{
  try
  {
    for (;;)
    {
      char data[max_length];
      boost::system::error_code error;
      size_t length = sock.read_some(boost::asio::buffer(data), error);
      std::cerr << "From client received: " << data << std::endl;
      if (error == boost::asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // Some other error.
      data[0] = 'E';
      data[1] = 'G';
      boost::asio::write(sock, boost::asio::buffer(data, length));
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception in thread: " << e.what() << "\n";
  }
}

void server(boost::asio::io_service& io_service, unsigned short port)
{
  tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
  for (;;)
  {
    tcp::socket sock(io_service);
    a.accept(sock);
    std::cout << "ACCEPT!!!" << std::endl;
    std::thread(session, std::move(sock)).detach();
  }
}

int main(int argc, char* argv[]) {
  try {
    if (argc != 2) {
      std::cerr << "Usage: blocking_tcp_echo_server <port>\n";
      return 1;
    }

    boost::asio::io_service io_service;

    auto m_thread = std::thread(server, std::ref(io_service), 8080);
    //server(io_service, std::atoi(argv[1]));
    std::cout << "HAHAHAHAH" << std::endl;
    m_thread.join();	
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
