#pragma once
#include <iostream>
#include "Globals.h"
#include "IRequestHandler.h"

class IRequestHandler;

typedef struct LoginRequest
{
	std::string username;
	std::string password;
}LoginRequest;

typedef struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
	std::string address;
	std::string phoneNumber;
	std::string birthDate;
}SignupRequest;

typedef struct GetPlayersInRoomRequest
{
	RoomID roomId;
}GetPlayersInRoomRequest;

typedef struct JoinRoomRequest
{
	RoomID roomId;
}JoinRoomRequest;

typedef struct CreateRoomRequest
{
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
}CreateRoomRequest;

typedef struct RequestResult
{
	Buffer buffer;
	IRequestHandler* newHandler;

	RequestResult() : newHandler(nullptr) {}
}RequestResult;

typedef struct RequestInfo
{
	RequestId id;
	std::time_t receivalTime;
	Buffer buffer;
}RequestInfo;