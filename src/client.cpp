#include "client.h"

void Client::resolve(std::string host, std::string port)
{
    resolver.async_resolve(host, port,
                                boost::bind(&Client::connectToServer, this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::results));
}




Client::Client(boost::asio::io_context& io_context, std::string host, std::string port) {
  resolver.async_resolve(server, port,
                          boost::bind(&Client::handle_resolve, this,
                                      boost::asio::placeholders::error,
                                      boost::asio::placeholders::results));
}

Client::~Client() {}