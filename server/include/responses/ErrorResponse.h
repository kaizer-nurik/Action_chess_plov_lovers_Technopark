#ifndef ERRORRESPONSE_H
#define ERRORRESPONSE_H

#include <string>

#include "BaseResponse.h"

struct ErrorResponse: public BaseResponse {
public:
    ErrorResponse() = default;

    std::string toJSON() override { return "error"; }

    virtual ~ErrorResponse() = default;    
};

#endif // ERRORRESPONSE_H