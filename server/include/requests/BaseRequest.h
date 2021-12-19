#ifndef BASEREQUEST_H
#define BASEREQUEST_H

 #include <string>

struct BaseRequest {
    virtual void parse(const std::string &requestData) = 0;
    
    bool valid() { return m_transformSuccess; }

protected:
    bool m_transformSuccess = true;
};

#endif // BASEREQUEST_H