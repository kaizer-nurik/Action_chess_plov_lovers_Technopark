#ifndef CLIENT_GAMERESPONSE_H
#define CLIENT_GAMERESPONSE_H

#include "BaseResponse.h"

struct GameResponse: public BaseResponse {
    int moveStatus;
    std::string tableFEN;
    int moveFrom;
    int moveTo;
    
    void parse(const std::string &requestData) override {
        boost::json::error_code ec;
        boost::json::value parsedData = boost::json::parse(requestData, ec);

        if (ec) {
            m_transformSuccess = false;
            return;
        }
        m_transformSuccess = true;

        moveStatus = parsedData.at("moveStatus").to_number<int>();
        tableFEN = boost::json::value_to<std::string>(parsedData.at("tableFEN"));
        moveFrom = parsedData.at("moveFrom").to_number<int>();
        moveTo = parsedData.at("moveTo").to_number<int>();
    }
};

#endif // CLIENT_GAMERESPONSE_H