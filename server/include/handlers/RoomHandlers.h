#ifndef ROOMHANDLERS_H
#define ROOMHANDLERS_H

#include "BaseHandler.h"
#include "RoomRequests.h"
#include "RoomResponses.h"

class CreateRoomHandler: public BaseHandler {
public:
    CreateRoomHandler() = default;
    
    void process(const BaseRequest* request, BaseResponse* response, ClientData& clientData, MainMenu& mainMenu) override {
        const CreateRoomRequest* roomRequest = dynamic_cast<const CreateRoomRequest*>(request);   
        CreateRoomResponse* roomResponse = dynamic_cast<CreateRoomResponse*>(response); 

        std::string roomId = clientData.id;
        mainMenu.roomController.createRoom(roomId, 2);
        const ClientData* mainMenuClient = mainMenu.removeClient(clientData.id);
        mainMenu.roomController.getRoom(roomId)->addClient(*mainMenuClient);
        clientData.position = { Location::Room, roomId };

        roomResponse->status = 0;
    }

    ~CreateRoomHandler() = default;
};

class EnterRoomHandler: public BaseHandler {
public:
    EnterRoomHandler() = default;
    
    void process(const BaseRequest* request, BaseResponse* response, ClientData& clientData, MainMenu& mainMenu) override {
        const EnterRoomRequest* roomRequest = dynamic_cast<const EnterRoomRequest*>(request);   
        EnterRoomResponse* roomResponse = dynamic_cast<EnterRoomResponse*>(response); 

        std::string roomId = roomRequest->roomId;

        const ClientData* mainMenuClient = mainMenu.removeClient(clientData.id);
        mainMenu.roomController.getRoom(roomId)->addClient(*mainMenuClient);
        clientData.position = { Location::Room, roomId };

        roomResponse->status = 0;
    }

    ~EnterRoomHandler() = default;
};

class LeaveRoomHandler: public BaseHandler {
public:
    LeaveRoomHandler() = default;
    
    void process(const BaseRequest* request, BaseResponse* response, ClientData& clientData, MainMenu& mainMenu) override {
        const LeaveRoomRequest* roomRequest = dynamic_cast<const LeaveRoomRequest*>(request);   
        LeaveRoomResponse* roomResponse = dynamic_cast<LeaveRoomResponse*>(response); 

        std::string roomId = clientData.position.second;
        const ClientData* roomClient = mainMenu.roomController.getRoom(roomId)->removeClient(clientData.id);
        mainMenu.addClient(*roomClient);
        clientData.position = { Location::MainMenu, "" };

        roomResponse->status = 0;    
    }

    ~LeaveRoomHandler() = default;
};

class GetRoomsHandler: public BaseHandler {
public:
    GetRoomsHandler() = default;
    
    void process(const BaseRequest* request, BaseResponse* response, ClientData& clientData, MainMenu& mainMenu) override {
        const GetRoomsRequest* roomRequest = dynamic_cast<const GetRoomsRequest*>(request);   
        GetRoomsResponse* roomResponse = dynamic_cast<GetRoomsResponse*>(response); 

        // ...
    }

    ~GetRoomsHandler() = default;
};

class StartGameHandler: public BaseHandler {
public:
    StartGameHandler() = default;
    
    void process(const BaseRequest* request, BaseResponse* response, ClientData& clientData, MainMenu& mainMenu) override {
        const StartGameRequest* roomRequest = dynamic_cast<const StartGameRequest*>(request);   
        StartGameResponse* roomResponse = dynamic_cast<StartGameResponse*>(response); 

        std::string roomId = clientData.position.second;
        mainMenu.roomController.getRoom(roomId)->startGame();
        clientData.position = { Location::Game, roomId };

        roomResponse->status = 0;    
    }

    ~StartGameHandler() = default;
};

#endif // ROOMHANDLERS_H