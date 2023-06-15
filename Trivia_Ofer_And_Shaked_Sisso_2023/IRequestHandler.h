#pragma once
#include <iostream>
#include "Globals.h"
#include "Requests.h"
#include "Responses.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"

struct RequestResult;
struct RequestInfo;


class IRequestHandler
{
public:
	virtual bool isRequestRelevent(const RequestInfo& info) = 0;
	virtual RequestResult handleRequest(const RequestInfo& info) = 0;
};
