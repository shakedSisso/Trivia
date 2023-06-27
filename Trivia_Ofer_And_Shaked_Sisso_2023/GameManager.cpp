#include "GameManager.h"
#include "LoggedUser.h"

GameManager::GameManager(IDatabase* database)
	: m_database(database)
{
}

GameID GameManager::createGame(const Room& room)
{
	vector<LoggedUser> usersList;
	auto questionsList = this->m_database->getQuestions(room.getRoomData().numOfQuestionsInGame, room.getIfIncludeUserQuestions());
	vector<Question> questions;
	for (auto& question : questionsList)
	{
		questions.push_back(question);
	}
	for (const auto& user : room.getAllUsers())
	{
		usersList.push_back(LoggedUser(user));
	}
	Game game(this->m_database, questions, usersList, room);
	this->m_games.push_back(game);
	return game.getGameId();
}

void GameManager::deleteGame(const GameID gameId)
{
	for (auto game = this->m_games.begin(); game != this->m_games.end(); game++)
	{
		if (game->getGameId() == gameId)
		{
			auto players = game->getPlayers();
			for (auto user : players)
			{
				delete(user.second);
			}
			this->m_games.erase(game);
			break;
		}
	}
}

Game GameManager::getGame(const GameID& gameId) const
{
	Game game;
	for (auto g : this->m_games)
	{
		if (g.getGameId() == gameId)
		{
			game = g;
		}
	}
	return game;
}

void GameManager::setDatabase(IDatabase* database)
{
	this->m_database = database;
}
