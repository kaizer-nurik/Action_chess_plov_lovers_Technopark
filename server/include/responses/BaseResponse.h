#ifndef BASERESPONSE_H
#define BASERESPONSE_H

#include <string>

struct BaseResponse {
public:
    BaseResponse() = default;

    virtual std::string toJSON() = 0;

    virtual ~BaseResponse() = default;
};

#endif // BASERESPONSE_H