#pragma once
#include <iostream>
#include <vector>
#include "SqliteDatabase.h"
#include "LoggedUser.h"

class LoginManager
{
public:
	LoginManager(IDatabase* database);
	void signup(const std::string username, const std::string password, const std::string mail, const std::string address, const std::string phoneNumber, const std::string birthDate);
	void login(const std::string username, const std::string password);
	void logout(const std::string username);
private:
	std::vector<LoggedUser> m_loggedUsers;
	IDatabase* m_database;

	bool isUserLoggedIn(const std::string username);
};