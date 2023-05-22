#include "RoomManager.h"

void RoomManager::createRoom(const LoggedUser& loggedUser, RoomData roomMetadata)
{
	this->m_rooms[roomMetadata.id] = Room(roomMetadata);
	this->m_rooms[roomMetadata.id].addUser(loggedUser);
}

void RoomManager::deleteRoom(RoomID roomId)
{
	auto iter = this->m_rooms.find(roomId);
	if (iter != this->m_rooms.end())
	{
		this->m_rooms.erase(iter);
	}
}

unsigned int RoomManager::getRoomState(RoomID roomId) const
{
	return this->m_rooms.at(roomId).getRoomData().isActive;
}

vector<RoomData> RoomManager::getRooms() const
{
	vector<RoomData> rooms;

	for (auto iter = this->m_rooms.begin(); iter != this->m_rooms.end(); iter++)
	{
		rooms.push_back(iter->second.getRoomData());
	}
	return rooms;
}

Room& RoomManager::getRoom(RoomID roomId) 
{
	return this->m_rooms.at(roomId);
}
