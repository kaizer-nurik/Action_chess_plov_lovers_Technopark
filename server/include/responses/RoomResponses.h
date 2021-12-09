#ifndef ROOMRESPONSES_H
#define ROOMRESPONSES_H

#include "BaseResponse.h"

struct EnterRoomResponse: public BaseResponse {
public:
    EnterRoomResponse() = default;

    std::string toJSON() override {}

    ~EnterRoomResponse() = default;

public:
    std::string method;
};

struct LeaveRoomResponse: public BaseResponse {
public:
    LeaveRoomResponse() = default;

    std::string toJSON() override {}

    ~LeaveRoomResponse() = default;

public:
    std::string method;
};

struct GetRoomsResponse: public BaseResponse {
public:
    GetRoomsResponse() = default;

    std::string toJSON() override {}

    ~GetRoomsResponse() = default;

public:
    std::string method;
};

#endif // ROOMRESPONSES_H