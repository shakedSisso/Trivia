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

	void createGame(const Room& room);
	void deleteGame(const int gameId);

private:
	IDatabase* m_database;
	vector<Game> m_games;
};
