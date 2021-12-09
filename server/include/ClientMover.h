#ifndef CLIENTMOVER_H
#define CLIENTMOVER_H

#include <boost/asio/ip/tcp.hpp>

#include "ClientData.h"

class IClientMover {
public:
    virtual void addClient(const ClientData& clientData) = 0;
    virtual void removeClient(std::string id) = 0;
    virtual boost::asio::ip::tcp::socket& getClientSocket(std::string id) = 0;
    virtual bool haveClient(std::string id) = 0;
};

#endif // CLIENTMOVER_H
