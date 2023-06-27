#pragma once
#include "SqliteDatabase.h"
#include "LoginManager.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "GameManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "GameRequestHandler.h"

class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class GameRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* database);
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser& user);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(LoggedUser& user, Room* room);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(LoggedUser& user, Room* room);
	GameRequestHandler* createGameRequestHandler(LoggedUser& user, Room& room, GameID gameId);

	LoginManager& getLoginManager();
	RoomManager& getRoomManager();
	StatisticsManager& getStatisticsManager();
	GameManager& getGameManager();

	/*
	* Function: setDatabase
	* ----------------------------
	*   The function gets a pointer to an IDatabase object and sets the m_database pointer to the given pointer
	*
	*   IDatabase* database: The new pointer to the database to set
	*
	*   returns: void.
	*/
	void setDatabase(IDatabase* db);

	IDatabase* getDatabase();

private:
	static int instanceCount;
	LoginManager m_loginManager;
	RoomManager m_roomManager;
	StatisticsManager m_statisticsManager;
	GameManager m_gameManager;
	IDatabase* m_database;
};