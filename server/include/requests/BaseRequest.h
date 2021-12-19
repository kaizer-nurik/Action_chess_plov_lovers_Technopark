#ifndef SERVER_BASEREQUEST_H
#define SERVER_BASEREQUEST_H

 #include <string>

struct BaseRequest {
    virtual void parse(const std::string &requestData) = 0;
    
    bool valid() { return m_transformSuccess; }

protected:
    bool m_transformSuccess = true;
};

#endif // SERVER_BASEREQUEST_H