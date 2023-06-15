#pragma once
#include <vector>
#include "IDatabase.h"
#include "Room.h"
#include "Game.h"

using std::vector;

class GameManager
{
public:
	GameManager(IDatabase* database);

	GameID createGame(const Room& room);
	void deleteGame(const GameID gameId);

	Game getGame(const GameID gameId);

	void setDatabase(IDatabase* database);

private:
	IDatabase* m_database;
	vector<Game> m_games;
};
