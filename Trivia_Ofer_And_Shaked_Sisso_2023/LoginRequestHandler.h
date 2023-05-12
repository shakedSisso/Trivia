#pragma once
#include <iostream>
#include "IRequestHandler.h"
#include "Requests.h"
#include "Responses.h"

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler() = default;
	bool isRequestRelevent(const RequestInfo& info) override;
	RequestResult handleRequest(const RequestInfo& info) override;
};