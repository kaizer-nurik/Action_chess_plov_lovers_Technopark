#ifndef ROOMHANDLERS_H
#define ROOMHANDLERS_H

#include "BaseHandler.h"
#include "RoomRequests.h"
#include "RoomResponses.h"

class EnterRoomHandler: public BaseHandler {
public:
    EnterRoomHandler() = default;
    
    void process(const BaseRequest* request, BaseResponse* response, ClientData& clientData, MainMenu& mainMenu) override {
        const EnterRoomRequest *roomRequest = dynamic_cast<const EnterRoomRequest*>(request);   
        EnterRoomResponse *roomResponse = dynamic_cast<EnterRoomResponse*>(response); 

        // ...
    }

    ~EnterRoomHandler() = default;
};

class LeaveRoomHandler: public BaseHandler {
public:
    LeaveRoomHandler() = default;
    
    void process(const BaseRequest* request, BaseResponse* response, ClientData& clientData, MainMenu& mainMenu) override {
        const LeaveRoomRequest *roomRequest = dynamic_cast<const LeaveRoomRequest*>(request);   
        LeaveRoomResponse *roomResponse = dynamic_cast<LeaveRoomResponse*>(response); 

        // ...
    }

    ~LeaveRoomHandler() = default;
};

class GetRoomsHandler: public BaseHandler {
public:
    GetRoomsHandler() = default;
    
    void process(const BaseRequest* request, BaseResponse* response, ClientData& clientData, MainMenu& mainMenu) override {
        const GetRoomsRequest *roomRequest = dynamic_cast<const GetRoomsRequest*>(request);   
        GetRoomsResponse *roomResponse = dynamic_cast<GetRoomsResponse*>(response); 

        // ...
    }

    ~GetRoomsHandler() = default;
};

#endif // ROOMHANDLERS_H