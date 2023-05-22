#include "Room.h"

Room::Room(const RoomData metadata)
	:m_metadata(metadata)
{
}

void Room::addUser(const LoggedUser& userToAdd)
{
	this->m_users.push_back(userToAdd);
}

void Room::removeUser(const LoggedUser& userToRemove)
{
	auto iter = std::find_if(m_users.begin(), m_users.end(),
		[&userToRemove](const LoggedUser& user) {
			return user.getUsename() == userToRemove.getUsename();
		});

	if (iter != m_users.end()) {
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
