#pragma once
#include <iostream>
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "IDatabase.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(RequestHandlerFactory& handlerFactory, IDatabase* database, LoggedUser& user, RoomManager& roomManager, StatisticsManager& statisticsManager);
	bool isRequestRelevent(const RequestInfo& info) override;
	RequestResult handleRequest(const RequestInfo& info) override;
private:
	IDatabase* m_database;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	StatisticsManager& m_statisticsManager;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult signout(const RequestInfo& info);
	RequestResult getRooms(const RequestInfo& info);
	RequestResult getPlayersInRoom(const RequestInfo& info);
	RequestResult getPersonalStats(const RequestInfo& info);
	RequestResult getHighScore(const RequestInfo& info);
	RequestResult joinRoom(const RequestInfo& info);
	RequestResult createRoom(const RequestInfo& info);
	RequestResult addQuestion(const RequestInfo& info);
	RequestResult joinHeadToHead(const RequestInfo& info);

	/*
	* Function: findHeadToHeadRoom const
	* ----------------------------
	*   The function gets a vector of rooms and searches for a room of headToHead mode and returns it's id if the rooms exists and HEAD_TO_HEAD_DOES_NOT_EXIST if not.
	*
	*   std::vector<RoomData> rooms: the vector of rooms to search for the id of the head to head room in
	*
	*   returns: int. The id of the head to head room is it exists and HEAD_TO_HEAD_DOES_NOT_EXIST if not
	*/
	int findHeadToHeadRoom(std::vector<RoomData> rooms) const;
	/*
	* Function: removeHeadToHeadRoomsFromTheList
	* ----------------------------
	*   The function gets a vector of rooms and removes the rooms of head to head mode from the vector
	*
	*   std::vector<RoomData> rooms: the vector of rooms
	*
	*   returns: void
	*/
	void removeHeadToHeadRoomsFromTheList(std::vector<RoomData>& rooms);
};