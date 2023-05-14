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
	Communicator(RequestHandlerFactory& handlerFactory);
	~Communicator();
	void startHandleRequests();

private:
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	RequestHandlerFactory& m_handlerFactory;

	void bindAndListen();
	void handleNewClient(SOCKET clientSocket);
};