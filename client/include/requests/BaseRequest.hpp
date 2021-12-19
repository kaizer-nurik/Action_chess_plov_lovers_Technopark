#ifndef CLIENT_BASEREQUEST_H
#define CLIENT_BASEREQUEST_H

 #include <string>

struct BaseRequest {
    virtual std::string toJSON() = 0;
};

#endif // CLIENT_BASEREQUEST_H