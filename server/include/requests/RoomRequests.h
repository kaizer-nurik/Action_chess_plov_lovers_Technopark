#ifndef ROOMREQUESTS_H
#define ROOMREQUESTS_H

#include <string>

#include "BaseRequest.h"

struct CreateRoomRequest: public BaseRequest {
    void parse(const std::string& requestData) override { return; }
};

struct EnterRoomRequest: public BaseRequest {
    std::string roomId;

    void parse(const std::string& requestData) override {
        roomId = requestData;
        m_transformSuccess = true;
    }
};

struct LeaveRoomRequest: public BaseRequest {
    void parse(const std::string& requestData) override { return; }
};

struct GetRoomsRequest: public BaseRequest {
    void parse(const std::string& requestData) override { return; }
};

struct StartGameRequest: public BaseRequest {
    void parse(const std::string& requestData) override { return; }
};

#endif // ROOMREQUESTS_H