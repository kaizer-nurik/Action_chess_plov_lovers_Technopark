#include "Client.hpp"

#include <boost/bind.hpp>
#include <iostream>

#include "Gamesession.hpp"

Client::Client(boost::asio::io_context& io_context, const std::string& server, const std::string& port)
        : m_resolver(io_context), m_socket(io_context) {
    m_resolver.async_resolve(server, port, boost::bind(&Client::onResolve, this,
                                                       boost::asio::placeholders::error,
                                                       boost::asio::placeholders::results));
}

void Client::onResolve(const boost::system::error_code& err, const boost::asio::ip::tcp::resolver::results_type& endpoints) {
    if (!err) {
        boost::asio::async_connect(m_socket, endpoints,
                                   boost::bind(&Client::onConnect, this,
                                               boost::asio::placeholders::error));
    } else {
        std::cout << "Error: " << err.message() << "\n";
    }
}

void Client::onConnect(const boost::system::error_code& err) {
    if (!err) {
        m_socket.async_read_some(boost::asio::buffer(m_readBuffer),
                             boost::bind(&Client::handleRead, this,
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
    } else {
        std::cout << "Error: " << err.message() << "\n";
    }
}

void Client::handleRead(const boost::system::error_code& err, std::size_t bytes_transferred) {
    if (!err) {
        m_readBuffer[bytes_transferred] = '\0';
        std::cout << "Read: " << m_readBuffer.data() << std::endl;

        std::string responseData = std::string(m_readBuffer.data());
        std::string method = getResponseMethod(responseData);
        
        // mapping will be later...
        
        if (method == "CreateRoom") {
            // handle
        } else if (method == "EnterRoom") {
            // handle
        } else if (method == "GameAction") {
            m_gameResponse.parse(getResponseJsonData(responseData));
            if (m_gameResponse.moveStatus != MOVE_ERROR) {
                // handle
            } else {
                // handle
            }
        } else if (method == "NewAction") {
            m_gameResponse.parse(getResponseJsonData(responseData));
            // handle
        } else {
            std::cout << "Error: undefined response" << std::endl;
        }

        m_socket.async_read_some(boost::asio::buffer(m_readBuffer),
                                 boost::bind(&Client::handleRead, this,
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred));
    } else {
        std::cout << "Error: " << err.message() << "\n";
    }
}

std::string Client::getResponseMethod(const std::string &responseData) {
    std::size_t pos = responseData.find(' ');
    if (pos == std::string::npos) {
        return "";
    }
    return responseData.substr(0, pos);
}

std::string Client::getResponseJsonData(const std::string &responseData) {
    std::size_t pos = responseData.find(' ');\
    if (pos == std::string::npos) {
        return "";
    }
    return responseData.substr(pos + 1, responseData.size() - pos - 1);
}