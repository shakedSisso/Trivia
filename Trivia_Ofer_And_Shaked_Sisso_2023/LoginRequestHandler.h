#pragma once
#include <iostream>
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(RequestHandlerFactory& handlerFactory, LoginManager& loginManager);
	bool isRequestRelevent(const RequestInfo& info) override;
	RequestResult handleRequest(const RequestInfo& info) override;
private:
	RequestHandlerFactory& m_handlerFactory;
	LoginManager& m_loginManager;

	RequestResult login(const RequestInfo& info);
	RequestResult signup(const RequestInfo& info);
};