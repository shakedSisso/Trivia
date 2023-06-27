#pragma comment (lib, "ws2_32.lib")

#include <ctime>
#include "Communicator.h"
#include <thread>
#include <exception>
#include "JsonRequestPacketDeserializer.h"
#include "IRequestHandler.h"
#include "Requests.h"
#include "LoginManager.h"
#include "RSACryptoAlgorithm.h"

#define PORT 1444
#define LEN_MSG_HEADERS 5
#define LENGTH_FIELD_INDEX 1
#define JSON_LENGTH_FIELD_LEN 4
#define SOCKET_SEND_ERROR -1
#define LEN_DOCUMENT_ID 12
#define BYTE_MASK 0xFF
#define BITS_IN_BYTE 8

int Communicator::instanceCount = 0;

Communicator::Communicator(RequestHandlerFactory& handlerFactory, IDatabase* database) :m_database(database), m_clients(), m_serverSocket(), m_handlerFactory(handlerFactory), m_cryptoAlgorithm(new RSACryptoAlgorithm(this->m_database))
{
	if (Communicator::instanceCount != 0)
	{
		throw std::exception("Communicator was already created once.");
	}
	instanceCount++;
}

void Communicator::setDatabase(IDatabase* database)
{
	this->m_database = database;
	this->m_cryptoAlgorithm->setDatabase(database);
}

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
	this->m_cryptoAlgorithm->createKeys();
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
			this->m_clients.insert(std::pair<SOCKET, IRequestHandler*>(client_socket, (IRequestHandler*)this->m_handlerFactory.createLoginRequestHandler()));
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
		std::string requestDataString;
		Buffer requestHeaderEncryptedBuffer;
		Buffer requestEncryptedBuffer;
		Buffer requestDecryptedBuffer;
		Buffer responseEncryptedBuffer;
		Buffer requestBuffer;
		RequestInfo requestInfo;
		std::string responseString;
		int sendingResult = 0;
		int jsonLength = 0;
		int bytesReceived = 0;
		char docIdArr[LEN_DOCUMENT_ID];

		auto userKeys = getUserKeys(clientSocket);
		sendServerKeysToClient(clientSocket);

		/*if (!bytesReceived)
		{
			throw std::exception("Error: client disconnected");
		}
		else if (bytesReceived == SOCKET_ERROR)
		{
			int lastErr = WSAGetLastError();
			std::string error = "Error: " + std::to_string(lastErr);
			throw std::exception(error.c_str());
		}
		std::string userDocId(docIdArr);*/
		while (true)
		{
			bytesReceived = recv(clientSocket, headers, LEN_MSG_HEADERS, 0); // the headers of any message are in a fixed size so we are getting them first
			if (!bytesReceived)
			{
				throw std::exception("Error: client disconnected");
			}
			else if (bytesReceived == SOCKET_ERROR)
			{
				int lastErr = WSAGetLastError();
				std::string error = "Error: " + std::to_string(lastErr);
				throw std::exception(error.c_str());
			}
			requestHeadersString = std::string(headers, LEN_MSG_HEADERS); // converting the headers to a string in order to create a buffer out if it
			requestHeaderEncryptedBuffer = Buffer(requestHeadersString.begin(), requestHeadersString.end());
			//requestBuffer = Buffer(requestHeadersString.begin(), requestHeadersString.end());
			requestBuffer = this->m_cryptoAlgorithm->decrypt(requestHeaderEncryptedBuffer);
			jsonLength = JsonRequestPacketDeserializer::extractIntFromBuffer(requestBuffer, LENGTH_FIELD_INDEX, JSON_LENGTH_FIELD_LEN); // using function of the desrializer class to get the length of the json
			data = new char[jsonLength];

			recv(clientSocket, data, jsonLength, 0);
			requestDataString = std::string(data, jsonLength); // converting the json char array to a string in order to connect it to the buffer
			delete[] data;
			data = nullptr;
			requestEncryptedBuffer = Buffer(requestDataString.begin(), requestDataString.end());
			requestDecryptedBuffer = this->m_cryptoAlgorithm->decrypt(requestEncryptedBuffer);
			requestBuffer.insert(requestBuffer.end(), requestDecryptedBuffer.begin(), requestDecryptedBuffer.end()); // connecting the json to the headers in the buffer
			
			// Creating and setting a requestInfo struct
			requestInfo.buffer = requestBuffer;
			requestInfo.id = requestBuffer[0];
			requestInfo.receivalTime = time(nullptr);

			// getting the client handler from the clients map
			auto client = this->m_clients.find(clientSocket);
			IRequestHandler* clientHandler = client->second;

			RequestResult result = clientHandler->handleRequest(requestInfo);
			
			if (result.newHandler != clientHandler) //if request fails, the newHandler is the same as the original
			{
				delete(client->second); // deleting the current handler of the client since the handlerRequest function gives us a new handler pointer
				this->m_clients[clientSocket] = result.newHandler;
			}
			responseEncryptedBuffer = this->m_cryptoAlgorithm->encrypt(result.buffer, userKeys[0], userKeys[1]);
			//responseString = std::string(result.buffer.begin(), result.buffer.end()); // converting the response buffer to a string in order that we'll be able to send it in the socket
			responseString = std::string(responseEncryptedBuffer.begin(), responseEncryptedBuffer.end());
			sendingResult = send(clientSocket, responseString.c_str(), responseString.size(), 0);
			if (sendingResult == SOCKET_SEND_ERROR)
			{
				std::string error = "Error sending message to client- " + std::to_string(clientSocket);
				throw std::exception(error.c_str());
			}
			if (result.newHandler == nullptr)
			{
				throw std::exception("Disconnecting from client");
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		closesocket(clientSocket); // Closing the socket (in the level of the TCP protocol)
	}

	//client removed from the map after disconnection
	auto client = this->m_clients.find(clientSocket);
	if (client->second != nullptr)
	{
		delete(client->second); //the second field in the nap is a pointer to IRequestHandler
	}
	this->m_clients.erase(clientSocket);
}

void Communicator::insertIntToBuffer(Buffer& buffer, const int num, const int bytes)
{
	int i = 0;
	for (int i = bytes - 1; i >= 0; i--)
	{
		unsigned char byte = (num >> (BITS_IN_BYTE * i)) & BYTE_MASK; // extract a byte from the int value
		buffer.push_back(byte); // add the byte to the vector
	}

}

std::vector<int> Communicator::getUserKeys(SOCKET clientSocket)
{
	std::vector<int> keys;
	int publicKey = 0;
	int bytesReceived = 0;
	char* data = nullptr;
	int publicKeyLen = 0;
	Buffer keysHeadersBuffer;
	std::string keysHeadersString;
	int userModulusLen = 0;
	int userModulus = 0;
	char userPublicKeyLenHeader[4];
	char userModulusLenHeader[4];

	bytesReceived = recv(clientSocket, userPublicKeyLenHeader, 4, 0);
	keysHeadersString = std::string(userPublicKeyLenHeader, 4);
	keysHeadersBuffer = Buffer(keysHeadersString.begin(), keysHeadersString.end());
	publicKeyLen = JsonRequestPacketDeserializer::extractIntFromBuffer(keysHeadersBuffer, 0, 4);
	data = new char[publicKeyLen];
	bytesReceived = recv(clientSocket, data, publicKeyLen, 0);
	publicKey = std::stoi(data);
	delete[] data;
	data = nullptr;

	bytesReceived = recv(clientSocket, userModulusLenHeader, 4, 0);
	keysHeadersString = std::string(userModulusLenHeader, 4);
	keysHeadersBuffer = Buffer(keysHeadersString.begin(), keysHeadersString.end());
	userModulusLen = JsonRequestPacketDeserializer::extractIntFromBuffer(keysHeadersBuffer, 0, 4);
	data = new char[userModulusLen];
	bytesReceived = recv(clientSocket, data, userModulusLen, 0);
	userModulus = std::stoi(data);
	delete[] data;
	data = nullptr;
	keys.push_back(publicKey);
	keys.push_back(userModulus);
	return keys;
}

void Communicator::sendServerKeysToClient(SOCKET clientSocket)
{
	std::string serverPublicKeyString;
	std::string serverModulusString;
	Buffer serverPublicKeyBuffer;
	Buffer serverModulusBuffer;
	int serverPublicKey = 0;
	int serverModulus = 0;
	std::string serverPublicKeyMessage;
	std::string serverModulusMessage;

	auto keys = this->m_cryptoAlgorithm->getKey();
	serverPublicKey = keys[0];
	serverModulus = keys[1];
	
	insertIntToBuffer(serverPublicKeyBuffer, std::to_string(serverPublicKey).size(), 4);
	serverPublicKeyString = std::to_string(serverPublicKey);
	serverPublicKeyBuffer.insert(serverPublicKeyBuffer.end(), serverPublicKeyString.begin(), serverPublicKeyString.end());
	serverPublicKeyMessage = std::string(serverPublicKeyBuffer.begin(), serverPublicKeyBuffer.end());
	send(clientSocket, serverPublicKeyMessage.c_str(), serverPublicKeyMessage.size(), 0);

	insertIntToBuffer(serverModulusBuffer, std::to_string(serverModulus).size(), 4);
	serverModulusString = std::to_string(serverModulus);
	serverModulusBuffer.insert(serverModulusBuffer.end(), serverModulusString.begin(), serverModulusString.end());
	serverModulusMessage = std::string(serverModulusBuffer.begin(), serverModulusBuffer.end());
	send(clientSocket, serverModulusMessage.c_str(), serverModulusMessage.size(), 0);
}
