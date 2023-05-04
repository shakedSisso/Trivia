#pragma once
#include <iostream>
#include "IRequestHandler.h"
#include "Requests.h"

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler() = default;
	bool isRequestRelevent(RequestInfo info) override;
	RequestResult handleRequest(RequestInfo info) override;
};