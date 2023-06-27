#pragma once
#include <iostream>
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "Game.h"

class RequestHandlerFactory;

class GameRequestHandler : public IRequestHandler
{
public:
	GameRequestHandler(RequestHandlerFactory& handlerFactory, GameManager& gameManager, GameID gameId, LoggedUser& user);
	bool isRequestRelevent(const RequestInfo& info) override;
	RequestResult handleRequest(const RequestInfo& info) override;
private:
	Game m_game;
	LoggedUser m_user;
	RequestHandlerFactory& m_handlerFactory;
	GameManager& m_gameManager;

	/*
	* Function: sortVector
	* ----------------------------
	*   The function gets an std::vector of PlayerResults and sorts the vector by the results of the players
	*
	*   std::vector<PlayerResults>& v: the vector to sort 
	*
	*   returns: void.
	*/
	void sortVector(std::vector<PlayerResults>& v);

	RequestResult getQuestion(const RequestInfo& info);
	RequestResult submitAnswer(const RequestInfo& info);
	RequestResult getGameResults(const RequestInfo& info);
	RequestResult leaveGame(const RequestInfo& info);
};