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

	/*
	* Function: getGame const
	* ----------------------------
	*   The function gets an id of a game and returns it's Game object
	*
	*   const GameID& gameId: the id of the game to get
	*
	*   returns: Game. The object of the game with the given id
	*/
	Game getGame(const GameID& gameId) const;

	/*
	* Function: setDatabase
	* ----------------------------
	*   The function gets a pointer to an IDatabase object and sets the m_database pointer to the given pointer
	*
	*   IDatabase* database: The new pointer to the database to set
	*
	*   returns: void.
	*/
	void setDatabase(IDatabase* database);

private:
	IDatabase* m_database;
	vector<Game> m_games;
};
