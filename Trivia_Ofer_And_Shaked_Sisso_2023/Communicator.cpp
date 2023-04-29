#pragma comment (lib, "ws2_32.lib")

#include "Communicator.h"
#include <thread>
#include <exception>
#include "LoginRequestHandler.h"

#define PORT 1444

void Communicator::startHandleRequests()
{
	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	this->m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (this->m_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(PORT); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(this->m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(this->m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");

	while (true)
	{
		// this accepts the client and create a specific socket from server to this client
		// the process will not continue until a client connects to the server
		SOCKET client_socket = accept(this->m_serverSocket, NULL, NULL);
		if (client_socket == INVALID_SOCKET)
			throw std::exception(__FUNCTION__);

		try
		{
			// the function that handle the conversation with the client
			std::thread newClient(&Communicator::handleNewClient, this, client_socket);
			newClient.detach();
			this->m_clients.insert(std::pair<SOCKET, IRequestHandler*>(client_socket, LoginRequestHandler*));
		}
		catch (std::exception e)
		{
			std::cerr << e.what() << std::endl;
			closesocket(client_socket);
		}
	}
}

void Communicator::handleNewClient(SOCKET clientSocket)
{
	try
	{
		std::string s = "Hello";
		send(clientSocket, s.c_str(), s.size(), 0);  // last parameter: flag. for us will be 0.

		char msg[6];
		recv(clientSocket, msg, 5, 0);
		msg[5] = 0;
		std::cout << "Client message: " << msg << std::endl;

		// Closing the socket (in the level of the TCP protocol)
		closesocket(clientSocket);
	}
	catch (const std::exception& e)
	{
		closesocket(clientSocket);
	}

	//client removed from the map after disconnection
	this->m_clients.erase(clientSocket);
}
