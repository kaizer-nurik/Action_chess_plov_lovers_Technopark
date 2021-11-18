#ifndef CLIENT_H
#define CLIENT_H

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>

using boost::asio::ip::tcp;

class Client {
 private:
  tcp::resolver resolver;
  tcp::socket socket;

  boost::asio::streambuf response_buf;

 public:
  Client(boost::asio::io_context& io_context, std::string host, std::string port); // resolve host name
  ~Client();
  private: 
  void resolve(std::string host, std::string port); 
  void connectToServer(const boost::system::error_code& err,
                        const tcp::resolver::results_type& endpoints);
  void sendRequest(const boost::system::error_code& err);
  void getResponse(const boost::system::error_code& err);
};



#endif  // CLIENT_H
