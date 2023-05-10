#pragma comment (lib, "ws2_32.lib")

#include <ctime>
#include "Communicator.h"
#include <thread>
#include <exception>
#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "IRequestHandler.h"
#include "Requests.h"

#define PORT 1444
#define LEN_MSG_HEADERS 5
#define LENGTH_FIELD_INDEX 1
#define JSON_LENGTH_FIELD_LEN 4
#define SOCKET_SEND_ERROR -1

Communicator::~Communicator()
{
	//frees all the client memories
	for (auto it = this->m_clients.begin(); it != this->m_clients.end(); ++it)
	{
		closesocket(it->first); // closes all the open sockets of clients
		delete(it->second); // the second field in the nap is a pointer to IRequestHandler
	}
}

void Communicator::startHandleRequests()
{
	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	this->m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (this->m_serverSocket == INVALID_SOCKET)
	{
		throw std::exception(__FUNCTION__ " - socket");
	}
	bindAndListen();
}

void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(PORT); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(this->m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
	{
		throw std::exception(__FUNCTION__ " - bind");
	}

	// Start listening for incoming requests of clients
	if (listen(this->m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		throw std::exception(__FUNCTION__ " - listen");
	}

	while (true)
	{
		// this accepts the client and create a specific socket from server to this client
		// the process will not continue until a client connects to the server
		SOCKET client_socket = accept(this->m_serverSocket, NULL, NULL);
		if (client_socket == INVALID_SOCKET)
		{
			throw std::exception(__FUNCTION__);
		}

		try
		{
			// the function that handle the conversation with the client
			std::thread newClient(&Communicator::handleNewClient, this, client_socket);
			newClient.detach();
			LoginRequestHandler* requestHandler = new LoginRequestHandler();
			this->m_clients.insert(std::pair<SOCKET, IRequestHandler*>(client_socket, (IRequestHandler*)requestHandler));
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
		char headers[LEN_MSG_HEADERS];
		char* data = nullptr;
		std::string requestHeadersString;
		std::string reqeustDataString;
		Buffer requestBuffer;
		RequestInfo requestInfo;
		std::string responseString;
		int sendingResult = 0;
		while (true)
		{
			recv(clientSocket, headers, LEN_MSG_HEADERS, 0);
			requestHeadersString = std::string(headers, LEN_MSG_HEADERS);
			requestBuffer = Buffer(requestHeadersString.begin(), requestHeadersString.end());
			int jsonLength = JsonRequestPacketDeserializer::extractIntFromBuffer(requestBuffer, LENGTH_FIELD_INDEX, JSON_LENGTH_FIELD_LEN);
			data = new char[jsonLength];
			recv(clientSocket, data, jsonLength, 0);
			reqeustDataString = std::string(data, jsonLength);
			delete[] data;
			data = nullptr;
			requestBuffer.insert(requestBuffer.end(), reqeustDataString.begin(), reqeustDataString.end());
			requestInfo.buffer = requestBuffer;
			requestInfo.id = requestBuffer[0];
			requestInfo.receivalTime == time(nullptr);
			auto client = this->m_clients.find(clientSocket);
			IRequestHandler* clientHandler = client->second;
			RequestResult result = clientHandler->handleRequest(requestInfo);
			delete(client->second);
			this->m_clients[clientSocket] = result.newHandler;
			responseString = std::string(result.buffer.begin(), result.buffer.end());
			sendingResult = send(clientSocket, responseString.c_str(), responseString.size(), 0);
			if (sendingResult == SOCKET_SEND_ERROR)
			{
				throw std::exception();
			}
		}
		// Closing the socket (in the level of the TCP protocol)
		closesocket(clientSocket);
	}
	catch (const std::exception& e)
	{
		closesocket(clientSocket);
	}

	//client removed from the map after disconnection
	auto client = this->m_clients.find(clientSocket);
	delete(client->second); //the second field in the nap is a pointer to IRequestHandler
	this->m_clients.erase(clientSocket);
}
