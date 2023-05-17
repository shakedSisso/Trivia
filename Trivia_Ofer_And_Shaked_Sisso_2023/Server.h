#pragma once
#include "Communicator.h"
#include "WSAInitializer.h"
#include "RequestHandlerFactory.h"
#include "SqliteDatabase.h"

class Server
{
public:
	void run();
	Server();
	
private:
	static int instanceCount;
	WSAInitializer _wasInitializer;
	Communicator m_communicator;
	RequestHandlerFactory m_handlerFactory;
	IDatabase* m_database;
};
