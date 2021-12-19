#include "GameWriter.h"

#include <boost/asio/write.hpp>

void GameWriter::onAction(boost::asio::ip::tcp::socket& socket, const std::string& response) {
    std::string writeBuffer = "NewAction " + response;
    boost::asio::write(socket, boost::asio::buffer(writeBuffer.data(), writeBuffer.size()));
}

