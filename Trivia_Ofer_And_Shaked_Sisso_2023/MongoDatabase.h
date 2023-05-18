#pragma once
#include "IDatabase.h"


#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/oid.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/database.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/write_concern.hpp>


#define ERROR_RESPONSE_CODE 1
#define FOUND_RESPONSE_CODE 2

class MongoDatabase : public IDatabase
{
public:
	MongoDatabase();
	bool open() override;
	bool close() override;
	int doesUserExist(const std::string username) override;
	int doesPasswordMatch(const std::string username, const std::string password) override;
	int addNewUser(const std::string username, const std::string password, const std::string mail, const std::string address, const std::string phoneNumber, const std::string birthDate) override;

private:
	mongocxx::uri _uri;
	mongocxx::client _client;
	mongocxx::database _db;

};