#pragma once
#include <regex>

#define PREFIX_ARR_LEN 16
#define DOMAIN_ARR_LEN 4
#define SPECIAL_CHAR_ARR_LEN 8
#define EMAIL_SYMBOL "@"

class RegexValidation
{
public:
	static bool isPasswordVaild(const std::string& password);
	static bool isEmailVlaid(const std::string& email);
	static bool isAddressVaild(const std::string& address);
	static bool isPhoneNumberValid(const std::string& phoneNumber);
	static bool isDataOfBirthValid(const std::string& birthDate);
};