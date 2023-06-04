#pragma once
#include <iostream>
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class RoomAdminRequestHandler : public IRequestHandler
{
public:
	RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, Room* room, LoggedUser& user, RoomManager& roomManager);
	bool isRequestRelevent(const RequestInfo& info) override;
	RequestResult handleRequest(const RequestInfo& info) override;
private:
	Room* m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult closeRoom(const RequestInfo& info);
	RequestResult startGame(const RequestInfo& info);
	RequestResult getRoomState(const RequestInfo& info);
};