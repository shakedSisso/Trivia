#include "Server.h"
#include <thread>
#include <iostream>

int Server::instanceCount = 0;

Server::Server() : m_communicator(this->m_handlerFactory), m_handlerFactory(nullptr)
//putting null in the the database variable because the database doesn't exist yet
{
	if (instanceCount != 0)
	{
		throw std::exception("Server was already created once.");
	}
	this->m_database = new SqliteDatabase();
	this->m_database->open();
	this->m_handlerFactory = RequestHandlerFactory(this->m_database);
	instanceCount++;
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