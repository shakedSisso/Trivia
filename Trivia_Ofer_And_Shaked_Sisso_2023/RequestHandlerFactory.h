#pragma once
#include "SqliteDatabase.h"
#include "LoginManager.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"

class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* database);
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser& user);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(LoggedUser& user, Room* room);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(LoggedUser& user, Room* room);

	LoginManager& getLoginManager();
	RoomManager& getRoomManager();
	StatisticsManager& getStatisticsManager();

	void setDatabase(IDatabase* db);

private:
	static int instanceCount;
	LoginManager m_loginManager;
	RoomManager m_roomManager;
	StatisticsManager m_statisticsManager;
	IDatabase* m_database;
};