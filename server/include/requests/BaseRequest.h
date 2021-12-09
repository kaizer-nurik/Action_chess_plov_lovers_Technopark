#ifndef BASEREQUEST_H
#define BASEREQUEST_H

#include <string>

class BaseRequest {
public:
    BaseRequest() = default;

    virtual void parse(const std::string &requestData) = 0;
    
    virtual ~BaseRequest() = default;

private:
    bool m_transformSuccess = true;
};

#endif // BASEREQUEST_H