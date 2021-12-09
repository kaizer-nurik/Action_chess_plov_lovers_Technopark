#ifndef ROOMREQUESTS_H
#define ROOMREQUESTS_H

#include <string>

#include "BaseRequest.h"

class EnterRoomRequest: public BaseRequest {
public:
    EnterRoomRequest() = default;

    void parse(const std::string& requestData) override {}

    ~EnterRoomRequest() = default;

private:
    unsigned int roomId;
};

class LeaveRoomRequest: public BaseRequest {
public:
    LeaveRoomRequest() = default;

    void parse(const std::string& requestData) override {}
    
    ~LeaveRoomRequest() = default;
};

class GetRoomsRequest: public BaseRequest {
public:
    GetRoomsRequest() = default;

    void parse(const std::string& requestData) override {}

    ~GetRoomsRequest() = default;
};

#endif // ROOMREQUESTS_H