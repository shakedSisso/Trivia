#include "LoginManager.h"

int LoginManager::instanceCount = 0;

LoginManager::LoginManager(IDatabase* database) : m_database(database)
{
	if (instanceCount != 0)
	{
		throw std::exception("Login manager was already created once.");
	}
	instanceCount++;
}

void LoginManager::signup(const std::string username, const std::string password, const std::string mail, const std::string address, const std::string phoneNumber, const std::string birthDate)
{
	if (this->m_database->doesUserExist(username) == ERROR_RESPONSE_CODE)
	{
		this->m_database->addNewUser(username, password, mail, address, phoneNumber, birthDate);
	}
	else
	{
		throw std::exception("Can't sign up- user already exists");
	}
}

void LoginManager::login(const std::string username, const std::string password)
{
	if (!isUserLoggedIn(username))
	{
		if (this->m_database->doesPasswordMatch(username, password) == FOUND_RESPONSE_CODE)
		{
			LoggedUser user(username);
			this->m_loggedUsers.push_back(user);
			return;
		}
		throw std::exception("Counldn't log in");
	}
	throw std::exception("Already logged in");
}

void LoginManager::logout(const std::string username)
{
	for (auto it  = this->m_loggedUsers.begin(); it != this->m_loggedUsers.end(); ++it)
	{
		if (it->getUsename() == username)
		{
			this->m_loggedUsers.erase(it);
			return;
		}
	}
}

void LoginManager::setDatabase(IDatabase* database)
{
	this->m_database = database;
}

bool LoginManager::isUserLoggedIn(const std::string username)
{
	for (auto it = this->m_loggedUsers.begin(); it != this->m_loggedUsers.end(); ++it)
	{
		if (it->getUsename() == username)
		{
			return true;
		}
	}
	return false;
}
