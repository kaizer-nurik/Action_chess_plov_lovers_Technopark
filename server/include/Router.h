#ifndef ROUTER_H
#define ROUTER_H

#include <boost/asio/ip/tcp.hpp>
#include <map>
#include <string>

#include "BaseHandler.h"
#include "BaseRequest.h"
#include "BaseResponse.h"
#include "ClientData.h"
#include "MainMenu.h"

class Router {
public:
    struct Steps {
        BaseRequest* request;
        BaseHandler* handler;
        BaseResponse* response;
    };

public:
    Router() = default;

    void addMethod(std::string method, Steps steps);
    std::string processRoute(const std::string &requestData, ClientData& m_clientData, MainMenu& m_mainMenu);

    ~Router();

private:
    std::string getRequestMethod(const std::string &requestData);
    std::string getRequestJsonData(const std::string &requestData);

    std::map<std::string, Steps> m_methodSteps;
};

#endif // ROUTER_H
