#include "SqliteDatabase.h"
#include <list>
#include <map>

SqliteDatabase::SqliteDatabase() : _db(), _dbFileName("triviaDB.sqlite")
{
}

int SqliteDatabase::callbackString(void* list, int argc, char** argv, char** azColName)
{
	int i = 0;
	for (i = 0; i < argc; i++)
	{
		((std::list<std::string>*)list)->push_back(argv[i]);
	}
	return 0;
}

bool SqliteDatabase::open()
{
	int res = sqlite3_open(this->_dbFileName.c_str(), &this->_db);
	if (res != SQLITE_OK)
	{
		this->_db = nullptr;
		std::cout << "Failed to open DB" << std::endl;
		return false;
	}
	return true;
}

bool SqliteDatabase::close()
{
	sqlite3_close(this->_db);
	this->_db = nullptr;
	return true;
}

int SqliteDatabase::doesUserExist(const std::string username)
{
	std::list<std::string> list;
	std::string sqlStatement = "SELECT * FROM t_users WHERE username = '" + username + "';";
	int res = sqlite3_exec(this->_db, sqlStatement.c_str(), callbackString, &list, nullptr);
	if (res != SQLITE_OK)
	{
		throw std::exception("Error\n");
	}
	if (list.empty())
	{
		return ERROR_RESPONSE_CODE;
	}
	return FOUND_RESPONSE_CODE;
}

int SqliteDatabase::doesPasswordMatch(const std::string username, const std::string password)
{
	if (doesUserExist(username) != ERROR_RESPONSE_CODE)
	{
		std::list<std::string> list;
		std::string sqlStatement = "SELECT password FROM t_users WHERE username = '" + username + "' AND password = '" + password + "'; ";
		int res = sqlite3_exec(this->_db, sqlStatement.c_str(), callbackString, &list, nullptr);
		if (res != SQLITE_OK)
		{
			throw std::exception("Error\n");
		}
		if (!list.empty())
		{
			return FOUND_RESPONSE_CODE;
		}
	}
	return ERROR_RESPONSE_CODE;

}

int SqliteDatabase::addNewUser(const std::string username, const std::string password, const std::string mail)
{
	std::string sqlStatement = "INSERT INTO t_users VALUES ('" + username + "', '" + password + "', '" + mail + "') ;";
	int res = sqlite3_exec(this->_db, sqlStatement.c_str(), nullptr, nullptr, nullptr);
	if (res != SQLITE_OK)
	{
		throw std::exception("Error\n");
	}
    return 0;
}
