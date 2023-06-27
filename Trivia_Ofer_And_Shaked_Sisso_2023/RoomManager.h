#pragma once
#include "Room.h"
#include "Globals.h"
#include "LoggedUser.h"
#include <map>
#include <vector>

using std::map;
using std::vector;

class RoomManager
{

public:
	void createRoom(const LoggedUser& loggedUser, RoomData roomMetadata, const bool includeUserQuestions);
	void deleteRoom(RoomID roomId);
	unsigned int getRoomState(RoomID roomId) const;
	vector<RoomData> getRooms() const;
	Room& getRoom(RoomID roomId);

private:
	map<RoomID, Room> m_rooms;

};