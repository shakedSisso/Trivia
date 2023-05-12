#pragma once
#include <iostream>
#include "IRequestHandler.h"
#include "Requests.h"

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler() = default;
	bool isRequestRelevent(const RequestInfo& info) override;
	RequestResult handleRequest(const RequestInfo& info) override;
};