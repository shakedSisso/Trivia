#pragma once
#include <iostream>

class LoggedUser
{
public:
	LoggedUser(const std::string username);
	std::string getUsename() const;
	bool operator<(const LoggedUser& other) const;
private:
	std::string m_username;
};