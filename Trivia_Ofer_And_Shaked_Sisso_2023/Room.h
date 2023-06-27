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
	/*
	* Function: getIfIncludeUserQuestions const
	* ----------------------------
	*   The function returns true if the admin of the room included user's added questions and false otherwise
	*
	*   input: none
	*
	*   returns: bool. true if the admin of the room included user's added questions and false otherwise
	*/
	bool getIfIncludeUserQuestions() const;
	/*
	* Function: activate
	* ----------------------------
	*   The function sets the isActive field of the RoomData to true
	*
	*   input: none
	*
	*   returns: void.
	*/
	void activate();

private:
	RoomData m_metadata;
	vector<LoggedUser> m_users;
	bool m_includeUserQuestions;

};