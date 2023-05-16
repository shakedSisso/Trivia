#pragma once
#include "Communicator.h"
#include "WSAInitializer.h"
#include "RequestHandlerFactory.h"
#include "SqliteDatabase.h"
#include "MongoDatabase.h"

class Server
{
public:
	Server();
	void run();
	
private:
	WSAInitializer _wasInitializer;
	Communicator m_communicator;
	RequestHandlerFactory m_handlerFactory;
	IDatabase* m_database;
};
