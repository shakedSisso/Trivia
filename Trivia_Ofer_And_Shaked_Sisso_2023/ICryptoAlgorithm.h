#pragma once
#include "Globals.h"
#include <string>
#include "IDatabase.h"
#include <vector>

using std::string;

class ICryptoAlgorithm
{
public:
	virtual Buffer encrypt(const Buffer& message, const int& key, const int& modulus) = 0;
	virtual Buffer decrypt(const Buffer& message) = 0;
	virtual void setDatabase(IDatabase* database) = 0;
	virtual void createKeys() = 0;
	virtual std::vector<int> getKey() = 0;
};