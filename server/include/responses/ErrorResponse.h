#ifndef ERRORRESPONSE_H
#define ERRORRESPONSE_H

#include <string>

#include "BaseResponse.h"

struct ErrorResponse: public BaseResponse {
    std::string toJSON() override { return "error"; }
};

#endif // ERRORRESPONSE_H