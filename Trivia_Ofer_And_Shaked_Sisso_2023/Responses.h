#pragma once
#include <string>
#include <vector>
#include "Room.h"

using std::string;
using std::vector;

typedef struct LoginResponse
{
	unsigned int status;
} LoginResponse;

typedef struct SignupResponse
{
	unsigned int status;
} SignupResponse;

typedef struct ErrorResponse
{
	string message;
} ErrorResponse;

typedef struct LogoutResponse
{
	unsigned int status;
} LogoutResponse;

typedef struct GetRoomsResponse
{
	unsigned int status;
	vector<RoomData> rooms;
} GetRoomsResponse;

typedef struct GetPlayersInRoomResponse
{
	vector<string> players;
} GetPlayersInRoomResponse;

typedef struct GetHighScoreResponse
{
	unsigned int status;
	vector<string> statistics;
} GetHighScoreResponse;

typedef struct GetPersonalStatsResponse
{
	unsigned int status;
	vector<string> statistics;
} GetPersonalStatsResponse;

typedef struct JoinRoomResponse
{
	unsigned int status;
} JoinRoomResponse;

typedef struct CreateRoomResponse
{
	unsigned int status;
} CreateRoomResponse;
