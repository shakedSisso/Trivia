#include "Room.h"

#define FALSE 0
#define TRUE !FALSE

Room::Room(const RoomData metadata, const bool includeUserQuestions)
	:m_metadata(metadata), m_includeUserQuestions(includeUserQuestions)
{
}

void Room::addUser(const LoggedUser& userToAdd)
{
	if (this->m_metadata.maxPlayers > this->m_users.size())
	{
		this->m_users.push_back(userToAdd);
	}
	else
	{
		throw std::exception("Room is full");
	}
}

void Room::removeUser(const LoggedUser& userToRemove)
{
	auto iter = std::find_if(m_users.begin(), m_users.end(),
		[&userToRemove](const LoggedUser& user) 
		{
			return user.getUsename() == userToRemove.getUsename();
		}); // checking if there is a user with the same username as the given user

	if (iter != m_users.end()) // checking if the user was found on the vector
	{
		m_users.erase(iter);
	}

	
}

vector<string> Room::getAllUsers() const
{
	vector<string> usersUsernames;

	for (auto iter = this->m_users.begin(); iter != this->m_users.end(); iter++)
	{
		usersUsernames.push_back(iter->getUsename());
	}
	return usersUsernames;
}

RoomData Room::getRoomData() const
{
	return this->m_metadata;
}

bool Room::getIfIncludeUserQuestions() const
{
	return this->m_includeUserQuestions;
}

void Room::activate()
{
	this->m_metadata.isActive = TRUE;
}
