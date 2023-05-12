#pragma once
#include <iostream>
#include "IRequestHandler.h"
#include "Requests.h"
#include "Responses.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(RequestHandlerFactory& handlerFactory);
	bool isRequestRelevent(const RequestInfo& info) override;
	RequestResult handleRequest(const RequestInfo& info) override;
private:
	RequestHandlerFactory& m_handlerFactory;

	RequestResult login(const RequestInfo& info);
	RequestResult signup(const RequestInfo& info);
};