#pragma once
#include "sqlite3.h"
#include "IDatabase.h"

#define ERROR_RESPONSE_CODE 1
#define FOUND_RESPONSE_CODE 2

class SqliteDatabase : public IDatabase
{
public:
	SqliteDatabase();
	bool open() override;
	bool close() override;
	int doesUserExist(const std::string username) override;
	int doesPasswordMatch(const std::string username, const std::string password) override;
	int addNewUser(const std::string username, const std::string password, const std::string mail, const std::string address, const std::string phoneNumber, const std::string birthDate) override;
private:
	sqlite3* _db;
	std::string _dbFileName;

	bool createTables(int& res);
	static int callbackString(void* list, int argc, char** argv, char** azColName);
};