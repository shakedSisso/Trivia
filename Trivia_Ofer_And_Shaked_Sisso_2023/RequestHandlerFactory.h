#pragma once
#include "SqliteDatabase.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"

class LoginRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* database);
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager* getLoginManager();
private:
	static int instanceCount;
	LoginManager m_loginManager;
	IDatabase* m_database;
};