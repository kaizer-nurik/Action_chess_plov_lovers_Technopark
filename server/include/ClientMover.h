#ifndef CLIENTMOVER_H
#define CLIENTMOVER_H

#include <boost/asio.hpp>

#include "ClientData.h"

class IClientMover {
public:
    virtual void addClient(const ClientData& clientData) = 0;
    virtual void removeClient(unsigned int id) = 0;
    virtual boost::asio::ip::tcp::socket& getClientSocket(unsigned int id) = 0;
    virtual bool haveClient(unsigned int id) = 0;
};

#endif // CLIENTMOVER_H
