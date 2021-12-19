#ifndef ROOMRESPONSES_H
#define ROOMRESPONSES_H

#include "BaseResponse.h"

struct CreateRoomResponse: public BaseResponse {
    int status;

    std::string toJSON() override {
        boost::json::object object({{ "status", status }});

        return boost::json::serialize(object);
    }
};

struct EnterRoomResponse: public BaseResponse {
    int status;

    std::string toJSON() override {
        boost::json::object object({{ "status", status }});

        return boost::json::serialize(object);
    }
};

struct LeaveRoomResponse: public BaseResponse {
    int status;

    std::string toJSON() override {
        boost::json::object object({{ "status", status }});

        return boost::json::serialize(object);
    }
};

struct GetRoomsResponse: public BaseResponse {
    std::string toJSON() override {}
};

struct StartGameResponse: public BaseResponse {
    int status;

    std::string toJSON() override {
        boost::json::object object({{ "status", status }});

        return boost::json::serialize(object);
    }
};

#endif // ROOMRESPONSES_H