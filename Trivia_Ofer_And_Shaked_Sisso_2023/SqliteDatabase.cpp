#include "SqliteDatabase.h"
#include <list>
#include <map>
#include <io.h>

SqliteDatabase::SqliteDatabase() : _db(), _dbFileName("triviaDB.sqlite")
{
}

bool SqliteDatabase::createTables(int& res)
{
	std::string sqlStatemant = "CREATE TABLE t_users ( username text primarykey NOT NULL, password text NOT NULL, email text NOT NULL, address TEXT NOT NULL, phone_number TEXT NOT NULL, birth_date TEXT NOT NULL);";
	char** errMessage = nullptr;
	res = sqlite3_exec(this->_db, sqlStatemant.c_str(), nullptr, nullptr, errMessage);
	if (res != SQLITE_OK)
		return false;
	sqlStatemant = "CREATE TABLE t_questions (question_id integer NOT NULL, question text NOT NULL, correct_ans text NOT NULL, ans2 text NOT NULL, ans3 text NOT NULL, ans4 text NOT NULL, PRIMARY KEY(question_id AUTOINCREMENT));";
	errMessage = nullptr;
	res = sqlite3_exec(this->_db, sqlStatemant.c_str(), nullptr, nullptr, errMessage);
	if (res != SQLITE_OK)
		return false;
	sqlStatemant = "CREATE TABLE t_players_answers ( game_id integer NOT NULL, username text NOT NULL, question_id integer NOT NULL, player_answer text NOT NULL, is_correct integer NOT NULL, answer_time integer NOT NULL, PRIMARY KEY(game_id,username,question_id), FOREIGN KEY(game_id) REFERENCES t_games(game_id), FOREIGN KEY(username) REFERENCES t_users(username), FOREIGN KEY(question_id) REFERENCES t_questions(question_id));";
	errMessage = nullptr;
	res = sqlite3_exec(this->_db, sqlStatemant.c_str(), nullptr, nullptr, errMessage);
	if (res != SQLITE_OK)
		return false;
	sqlStatemant = "CREATE TABLE t_games(game_id integer NOT NULL, status integer NOT NULL, start_time DATETIME NOT NULL, end_time DATETIME, PRIMARY KEY(game_id AUTOINCREMENT));";
	errMessage = nullptr;
	res = sqlite3_exec(this->_db, sqlStatemant.c_str(), nullptr, nullptr, errMessage);
	if (res != SQLITE_OK)
		return false;
	return true;
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
	int fileExist = _access(this->_dbFileName.c_str(), 0);
	int res = sqlite3_open(this->_dbFileName.c_str(), &this->_db);
	if (res != SQLITE_OK)
	{
		this->_db = nullptr;
		std::cout << "Failed to open DB" << std::endl;
		return false;
	}

	if (fileExist != 0)
	{
		if (!createTables(res))
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
		throw std::exception("Error- sqlite3_exec functions failed");
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
			throw std::exception("Error- sqlite3_exec functions failed");
		}
		if (!list.empty())
		{
			return FOUND_RESPONSE_CODE;
		}
	}
	return ERROR_RESPONSE_CODE;

}

int SqliteDatabase::addNewUser(const std::string username, const std::string password, const std::string mail, const std::string address, const std::string phoneNumber, const std::string birthDate)
{
	std::string sqlStatement = "INSERT INTO t_users VALUES ('" + username + "', '" + password + "', '" + mail + "', '" + address + "', '" + phoneNumber + "', '" + birthDate + "');";
	int res = sqlite3_exec(this->_db, sqlStatement.c_str(), nullptr, nullptr, nullptr);
	if (res != SQLITE_OK)
	{
		throw std::exception("Error- sqlite3_exec functions failed");
	}
    return 0;
}
