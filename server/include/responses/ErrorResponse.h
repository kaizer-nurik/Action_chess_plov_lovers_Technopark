#ifndef SERVER_ERRORRESPONSE_H
#define SERVER_ERRORRESPONSE_H

#include <string>

#include "BaseResponse.h"

struct ErrorResponse: public BaseResponse {
    std::string toJSON() override { return "ERROR"; }
};

#endif // SERVER_ERRORRESPONSE_H