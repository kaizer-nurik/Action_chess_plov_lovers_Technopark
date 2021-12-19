#ifndef CLIENT_GAMEREQUEST_H
#define CLIENT_GAMEREQUEST_H

#include "BaseRequest.h"

struct GameRequest: public BaseRequest {
    std::string move;

    std::string toJSON() override {
        return "GameAction " + move;
    }
};

#endif // CLIENT_GAMEREQUEST_H