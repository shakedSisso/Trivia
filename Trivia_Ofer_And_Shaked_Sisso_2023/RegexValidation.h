#pragma once
#include <regex>

class RegexValidation
{
public:
	static bool isPasswordVaild(const std::string& password);
	static bool isEmailVlaid(const std::string& email);
	static bool isAddressVaild(const std::string& address);
	static bool isPhoneNumberValid(const std::string& phoneNumber);
	static bool isDataOfBirthValid(const std::string& birthDate);
};