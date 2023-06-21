#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include "IRequestHandler.h"
#include <iostream>
#include <map>
#include "RequestHandlerFactory.h"
#include "ICryptoAlgorithm.h"
#include "IDatabase.h"

class Communicator
{
public:
	~Communicator();
	void startHandleRequests();
	Communicator(RequestHandlerFactory& handlerFactory, IDatabase* database);

	void setDatabase(IDatabase* database);

private:
	static int instanceCount;
	IDatabase* m_database;
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	RequestHandlerFactory& m_handlerFactory;
	ICryptoAlgorithm* m_cryptoAlgorithm;

	void bindAndListen();
	void handleNewClient(SOCKET clientSocket);
	void insertIntToBuffer(Buffer& buffer, const int num, const int bytes);
	std::vector<int> getUserKeys(SOCKET clientSocket);
	void sendSeverKeysToClient(SOCKET clientSocket);
};