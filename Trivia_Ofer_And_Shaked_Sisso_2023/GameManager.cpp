#include "GameManager.h"
#include "LoggedUser.h"

GameManager::GameManager(IDatabase* database)
	: m_database(database)
{
}

void GameManager::createGame(const Room& room)
{
	vector<LoggedUser> usersList;
	auto questionsList = this->m_database->getQuestions(room.getRoomData().numOfQuestionsInGame);
	vector<Question> questions(questionsList.begin(), questionsList.end());
	for (const auto& user : room.getAllUsers())
	{
		usersList.push_back(LoggedUser(user));
	}
	this->m_games.push_back(Game(questions,usersList, room));
}

void GameManager::deleteGame(const int gameId)
{
	for (auto game = this->m_games.begin(); game != this->m_games.end(); game++)
	{
		if (game->getGameId() == gameId)
		{
			map<LoggedUser, GameData> gamePlayers = game->getPlayers();
			for (auto player = gamePlayers.begin(); player != gamePlayers.end(); player++)
			{
				this->m_database->insertStatistics(player->first.getUsename(), player->second.correctAnswerCount, player->second.wrongAnswerCount, player->second.averageAnswerTime);
			}
			this->m_games.erase(game);
			break;
		}
	}
}
