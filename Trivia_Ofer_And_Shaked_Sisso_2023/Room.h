#pragma once
#include "LoggedUser.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

typedef struct RoomData
{
	unsigned int id;
	string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;
} RoomData;

class Room
{
public:
	Room() = default;
	Room(const RoomData metadata);
	void addUser(const LoggedUser& userToAdd);
	void removeUser(const LoggedUser& userToRemove);
	vector<string> getAllUsers() const;
	RoomData getRoomData() const;

private:
	RoomData m_metadata;
	vector<LoggedUser> m_users;

};