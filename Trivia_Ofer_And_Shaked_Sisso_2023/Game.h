#pragma once
#include "Question.h"
#include "LoggedUser.h"
#include "Room.h"
#include <map>
#include <vector>

using std::map;
using std::vector;

typedef struct GameData
{
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	float averageAnswerTime;
	GameData()
	{
		correctAnswerCount = 0;
		wrongAnswerCount = 0;
		averageAnswerTime = 0.0;
	}
} GameData;

class Game
{
public:
	Game(vector<Question> questions, vector<LoggedUser> users, const Room& room);

	Question getQuestionForUser(const LoggedUser& user) const;
	int submitAnswer(const LoggedUser& user, int answerId);
	void removePlayer(const LoggedUser& user);
	
	int getGameId() const;
	map<LoggedUser, GameData> getPlayers() const;
	bool isGameFinished() const;
private:
	vector<Question> m_questions;
	map<LoggedUser, GameData> m_players;
	int m_gameId;
	RoomData m_gameSettings;
};