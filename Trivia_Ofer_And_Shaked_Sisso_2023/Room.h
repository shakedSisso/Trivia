#pragma once
#include "LoggedUser.h"
#include "Globals.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

typedef struct RoomData
{
	RoomID id;
	string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;
	unsigned int isDuo;
} RoomData;

class Room
{
public:
	Room() = default;
	Room(const RoomData metadata, const bool includeUserQuestions);
	void addUser(const LoggedUser& userToAdd);
	void removeUser(const LoggedUser& userToRemove);
	vector<string> getAllUsers() const;
	RoomData getRoomData() const;
	bool getIfIncludeUserQuestions() const;
	void activate();

private:
	RoomData m_metadata;
	vector<LoggedUser> m_users;
	bool m_includeUserQuestions;

};