#pragma once
#include "Globals.h"
#include <string>

using std::string;

class ICryptoAlgorithm
{
public:
	virtual Buffer encrypt(const Buffer& message, const int& key, const int& modulus) = 0;
	virtual Buffer decrypt(const Buffer& message) = 0;
};