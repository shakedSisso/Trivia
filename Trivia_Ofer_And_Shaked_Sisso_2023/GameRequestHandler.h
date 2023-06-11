#pragma once
#include <iostream>
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class GameRequestHandler : public IRequestHandler
{
public:
	GameRequestHandler(RequestHandlerFactory& handlerFactory, GameManager& gameManager, Game game, LoggedUser& user);
	bool isRequestRelevent(const RequestInfo& info) override;
	RequestResult handleRequest(const RequestInfo& info) override;
private:
	Game& m_game;
	LoggedUser& m_user;
	RequestHandlerFactory& m_handlerFactory;
	GameManager& m_gameManager;

	RequestResult getQuestion(const RequestInfo& info);
	RequestResult submitAnswer(const RequestInfo& info);
	RequestResult getGameResults(const RequestInfo& info);
	RequestResult leaveGame(const RequestInfo& info);
};