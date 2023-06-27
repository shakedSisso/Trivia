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
	Game();
	Game(IDatabase* database, vector<Question> questions, vector<LoggedUser> users, const Room& room);

	Question getQuestionForUser(const LoggedUser& user);
	int submitAnswer(const LoggedUser& user, int answerId, int answeringTime);
	void removePlayer(const LoggedUser& user);
	
	/*
	* Function: getGameId const
	* ----------------------------
	*   The function returns the GameID of the game object
	*
	*   input: none
	*
	*   returns: GameID. The id of the game object
	*/
	GameID getGameId() const;
	/*
	* Function: getPlayers const
	* ----------------------------
	*   The function returns the map of users the pointers to their game data
	*
	*   input: none
	*
	*   returns: std::map<LoggedUser, GameData*>. The map of players in the game and their GameData pointers mapped to their username
	*/
	map<LoggedUser, GameData*> getPlayers() const;
	/*
	* Function: isGameFinished const
	* ----------------------------
	*   The function checks if all players in the game has finished their questions and return true if all players finished and false otherwise
	*
	*   input: none
	*
	*   returns: bool. True if all players has finished and false if not
	*/
	bool isGameFinished() const;
	/*
	* Function: areAllPlayersLoggedOut const
	* ----------------------------
	*   The function checks if all players in the game has a question LOG_OUT and true if this is the case and false if not
	*
	*   input: none
	*
	*   returns: bool. True if all players has question LOG_OUT and otherwise false
	*/
	bool areAllPlayersLoggedOut() const;
private:
	IDatabase* m_database;
	vector<Question> m_questions;
	map<LoggedUser, GameData*> m_players;
	GameID m_gameId;
	RoomData m_gameSettings;
};