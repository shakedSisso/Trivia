#pragma once
#include "Communicator.h"
#include "WSAInitializer.h"

class Server
{
public:
	void run();
	
private:
	WSAInitializer _wasInitializer;
	Communicator m_communicator;
};
