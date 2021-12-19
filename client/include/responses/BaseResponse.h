#ifndef CLIENT_BASERESPONSE_H
#define CLIENT_BASERESPONSE_H

#include <boost/json.hpp>
#include <string>

struct BaseResponse {
    virtual void parse(const std::string &requestData) = 0;
    
    bool valid() { return m_transformSuccess; }

protected:
    bool m_transformSuccess = true;
};

#endif // CLIENT_BASERESPONSE_H