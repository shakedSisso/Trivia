#pragma once
#include <iostream>
#include "IRequestHandler.h"
#include "Requests.h"

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler() = default;
	bool isRequestRelevent(RequestInfo info) override;
	RequestResult handleRequest(RequestInfo info) override;
};