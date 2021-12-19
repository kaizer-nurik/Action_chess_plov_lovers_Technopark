#ifndef GAMERESPONSE_H
#define GAMERESPONSE_H

#include "BaseResponse.h"

struct GameResponse: public BaseResponse {
    int moveStatus;
    std::string tableFEN;
    int moveFrom;
    int moveTo;

    std::string toJSON() override {
        boost::json::object object({{ "moveStatus", moveStatus }, 
                                    { "tableFEN",   tableFEN   },
                                    { "moveFrom",   moveFrom   },
                                    { "moveTo",     moveTo     }});

        return boost::json::serialize(object);
    }
};

#endif // GAMERESPONSE_H