#ifndef CLIENT_H
#define CLIENT_H

#include <boost/array.hpp>
#include <boost/asio.hpp>

#define MAX_IP_PACK_SIZE 8192

class Client {
public:
    Client(boost::asio::io_context& io_context, const std::string& server, const std::string& port);
    
    ~Client() = default;

private:
    void onResolve(const boost::system::error_code& err, const boost::asio::ip::tcp::resolver::results_type& endpoints);
    void onConnect(const boost::system::error_code& err);
    
    void handleRead(const boost::system::error_code& err, std::size_t bytes_transferred);

private:
    boost::asio::ip::tcp::resolver m_resolver;
    boost::asio::ip::tcp::socket m_socket;

    boost::array<char, MAX_IP_PACK_SIZE> m_readBuffer; 
};

#endif // CLIENT_H