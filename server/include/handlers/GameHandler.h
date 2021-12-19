#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include "BaseHandler.h"
#include "GameRequest.h"
#include "GameResponse.h"

#include "GameLogic.h"

class GameHandler: public BaseHandler {
public:
    GameHandler() = default;
    
    void process(const BaseRequest* request, BaseResponse* response, ClientData& clientData, MainMenu& mainMenu) override {
        const GameRequest *gameRequest = dynamic_cast<const GameRequest*>(request);   
        GameResponse *gameResponse = dynamic_cast<GameResponse*>(response); 

        Game clientGame = mainMenu.roomController.getRoom(clientData.position.second)->getGame();
        std::string move = gameRequest->move;
        return_after_move moveResult = clientGame.makeAction(clientData.id, move);

        gameResponse->moveStatus = moveResult.moveStatus;
        gameResponse->tableFEN = moveResult.table_fen;
        gameResponse->moveFrom = moveResult.move_from;
        gameResponse->moveTo = moveResult.move_to;

        if (moveResult.moveStatus != MOVE_ERROR) {
            clientGame.broadcast(clientData.id, gameResponse->toJSON());
        }
    }

    ~GameHandler() = default;
};

#endif // GAMEHANDLER_H