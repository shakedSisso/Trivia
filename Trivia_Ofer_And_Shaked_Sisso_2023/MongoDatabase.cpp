#include "MongoDatabase.h"

MongoDatabase::MongoDatabase()
{
}

bool MongoDatabase::open()
{
	return false;
}

bool MongoDatabase::close()
{
	return false;
}

int MongoDatabase::doesUserExist(const std::string username)
{
	return 0;
}

int MongoDatabase::doesPasswordMatch(const std::string username, const std::string password)
{
	return 0;
}

int MongoDatabase::addNewUser(const std::string username, const std::string password, const std::string mail)
{
	return 0;
}
