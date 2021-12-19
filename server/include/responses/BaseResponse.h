#ifndef BASERESPONSE_H
#define BASERESPONSE_H

 #include <boost/json.hpp>
 #include <string>

struct BaseResponse {
    virtual std::string toJSON() = 0;
};

#endif // BASERESPONSE_H