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
}SignupRequest;

typedef struct RequestResult
{
	Buffer buffer;
	IRequestHandler* newHandler;
}RequestResult;

typedef struct RequestInfo
{
	RequestId id;
	std::time_t receivalTime;
	Buffer buffer;
}RequestInfo;