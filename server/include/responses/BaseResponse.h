#ifndef SERVER_BASERESPONSE_H
#define SERVER_BASERESPONSE_H

 #include <boost/json.hpp>
 #include <string>

struct BaseResponse {
    virtual std::string toJSON() = 0;
};

#endif // SERVER_BASERESPONSE_H