#ifndef BASEHANDLER_H
#define BASEHANDLER_H

#include "BaseRequest.h"
#include "BaseResponse.h"
#include "ClientData.h"
#include "MainMenu.h"

class BaseHandler {
public:
    BaseHandler() = default;
    
    virtual void process(const BaseRequest* request, BaseResponse* response, ClientData& m_clientData, MainMenu& m_mainMenu) = 0;

    virtual ~BaseHandler() = default;
};

#endif // BASEHANDLER_H