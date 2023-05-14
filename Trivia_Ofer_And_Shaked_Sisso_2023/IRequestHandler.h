#pragma once
#include <iostream>
#include "Globals.h"
#include "Requests.h"

struct RequestResult;
struct RequestInfo;

#define LOGIN_REQUEST 1
#define SIGN_UP_REQUEST 2

class IRequestHandler
{
public:
	virtual bool isRequestRelevent(const RequestInfo& info) = 0;
	virtual RequestResult handleRequest(const RequestInfo& info) = 0;
};
