#pragma once
#include <iostream>

class IDatabase
{
public:
	IDatabase();
	virtual bool open() = 0;
	virtual bool close() = 0;
	virtual int doesUserExist(const std::string username) = 0;
	virtual int doesPasswordMatch(const std::string username, const std::string password) = 0;
	virtual int addNewUser(const std::string username, const std::string password, const std::string mail, const std::string address, const std::string phoneNumber, const std::string birthDate) = 0;
};