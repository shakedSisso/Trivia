#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include "IRequestHandler.h"
#include <iostream>
#include <map>
#include "RequestHandlerFactory.h"

class Communicator
{
public:
	~Communicator();
	void startHandleRequests();
	Communicator(RequestHandlerFactory& handlerFactory);


private:
	static int instanceCount;
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	RequestHandlerFactory& m_handlerFactory;

	void bindAndListen();
	void handleNewClient(SOCKET clientSocket);
};