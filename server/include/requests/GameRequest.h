#ifndef SERVER_GAMEREQUEST_H
#define SERVER_GAMEREQUEST_H

#include "BaseRequest.h"

struct GameRequest: public BaseRequest {
    std::string move;

    void parse(const std::string &requestData) override {
        if (requestData.size() == 4 && isValidCoord(requestData.substr(0, 2)) && isValidCoord(requestData.substr(2, 2))) {
            move = requestData;
            m_transformSuccess = true;
        } else {
            m_transformSuccess = false;
        }    
    }

private:
    bool isValidCoord(const std::string& coord) {
        return (coord.size() == 2 && isBoardLetter(coord[0]) && isBoardDigit(coord[1]));
    }

    bool isBoardDigit(char c) {
        return ('1' <= c && c <= '8');
    }

    bool isBoardLetter(char c) {
        return ('A' <= c && c <= 'H');
    }
};

#endif // SERVER_GAMEREQUEST_H