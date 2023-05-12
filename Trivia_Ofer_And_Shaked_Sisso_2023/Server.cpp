#include "Server.h"
#include <thread>
#include <iostream>

Server::Server() : m_communicator(this->m_handlerFactory), m_handlerFactory(nullptr)
//putting null in the the database variable because the database doesn't exist yet
{
	this->m_database = new SqliteDatabase();
	this->m_database->open();
	this->m_handlerFactory = RequestHandlerFactory(this->m_database);
}

void Server::run()
{
	std::thread connectorThread(&Communicator::startHandleRequests, &this->m_communicator);
	connectorThread.detach();
	std::string adminInput;
	
	do
	{
		std::cin >> adminInput;
	} while (adminInput != "EXIT");

	this->m_database->close();
	delete(this->m_database);
}
