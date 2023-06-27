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

	/*
	* Function: setDatabase
	* ----------------------------
	*   The function gets a pointer to an IDatabase object and sets the m_database pointer to the given pointer
	*
	*   IDatabase* database: The new pointer to the database to set
	*
	*   returns: void.
	*/
	void setDatabase(IDatabase* database);
private:
	static int instanceCount;
	std::vector<LoggedUser> m_loggedUsers;
	IDatabase* m_database;

	/*
	* Function: isUserLoggedIn const
	* ----------------------------
	*   The function gets a username string and checks if the given username is in the vector of LoggedUsers 
	*	and returns true if the user if found in the vector and false otherwise.
	*
	*   const std::string& username: The user to look for in the vector of LoggedUsers
	*
	*   returns: bool. true if the username is found and false otherwise
	*/
	bool isUserLoggedIn(const std::string& username) const;
};