#include "Server.h"
#include <thread>
#include <iostream>

void Server::run()
{
	std::thread connectorThread(&Communicator::startHandleRequests(), &this->m_communicator);
	connectorThread.detach();
	std::string adminInput;
	
	do
	{
		std::cin >> adminInput;
	} while (adminInput != "EXIT");
}
