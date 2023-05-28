#pragma once
#include <iostream>
#include "Globals.h"
#include "Requests.h"
#include "Responses.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"

struct RequestResult;
struct RequestInfo;

#define LOGIN_REQUEST 1
#define SIGN_UP_REQUEST 2
#define GET_PLAYERS_IN_ROOM_REQUEST 3
#define JOIN_ROOM_REQUEST 4
#define CREATE_ROOM_REQUEST 5
#define HIGH_SCORE_REQUEST 6
#define LOGOUT_REQUEST 7
#define GET_ROOMS_REQUEST 8
#define GET_STATISTICS 9


class IRequestHandler
{
public:
	virtual bool isRequestRelevent(const RequestInfo& info) = 0;
	virtual RequestResult handleRequest(const RequestInfo& info) = 0;
};
