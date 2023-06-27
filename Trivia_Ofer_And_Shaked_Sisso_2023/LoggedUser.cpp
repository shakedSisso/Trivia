#include "LoggedUser.h"

LoggedUser::LoggedUser(const std::string username)
{
	this->m_username = username;
}

std::string LoggedUser::getUsename() const
{
	return this->m_username;
}

bool LoggedUser::operator<(const LoggedUser& other) const
{
	return this->getUsename() < other.getUsename();
}
