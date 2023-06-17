#pragma once
#include "Question.h"
#include "LoggedUser.h"
#include "Room.h"
#include "Globals.h"
#include "IDatabase.h"
#include <map>
#include <vector>

using std::map;
using std::vector;

#define LOG_OUT "Logged out"

typedef struct GameData
{
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	float averageAnswerTime;
	GameData()
	{
		currentQuestion = Question();
		correctAnswerCount = 0;
		wrongAnswerCount = 0;
		averageAnswerTime = 0.0;
	}
} GameData;

class Game
{
public:
	Game() = default;
	Game(IDatabase* database, vector<Question> questions, vector<LoggedUser> users, const Room& room);

	Question getQuestionForUser(const LoggedUser& user);
	int submitAnswer(const LoggedUser& user, int answerId, int answeringTime);
	void removePlayer(const LoggedUser& user);
	
	GameID getGameId() const;
	map<LoggedUser, GameData*> getPlayers() const;
	bool isGameFinished() const;
private:
	IDatabase* m_database;
	vector<Question> m_questions;
	map<LoggedUser, GameData*> m_players;
	GameID m_gameId;
	RoomData m_gameSettings;
};