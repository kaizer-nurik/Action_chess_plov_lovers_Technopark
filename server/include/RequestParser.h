#ifndef REQUESTPARSER_H
#define REQUESTPARSER_H

#include <boost/array.hpp>

enum Protocol: unsigned {
    MAX_IP_PACK_SIZE = 8192
};

class RequestParser {
public:
    RequestParser(const boost::array<char, 8192>& request);
    void parse();
    
private:
    boost::array<char, MAX_IP_PACK_SIZE> m_request;
};

#endif // REQUESTPARSER_H
