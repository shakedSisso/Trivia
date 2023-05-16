#pragma once
#include "RegexValidation.h"

bool RegexValidation::isPasswordVaild(const std::string& password)
{
    std::regex pattern("^(?=.*[A-Z])(?=.*[a-z])(?=.*[0-9])(?=.*[^A-Za-z0-9]).{8,}$");
    if (std::regex_match(password, pattern))
    {
        return true;
    }
    return false;
}

bool RegexValidation::isEmailVlaid(const std::string& email)
{
    std::regex pattern("(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");
    if (std::regex_match(email, pattern))
    {
        return true;
    }
    return false;
}

bool RegexValidation::isAddressVaild(const std::string& address)
{
    std::string pattern = R"(^\(\s*([^,]+)\s*,\s*([0-9]+)\s*,\s*([^,]+)\s*\)$)";
    if (std::regex_match(address, std::regex(pattern)))
    {
        return true;
    }
    return false;
}

bool RegexValidation::isPhoneNumberValid(const std::string& phoneNumber)
{
    if (std::regex_match(phoneNumber, std::regex("^(0\\d{1,2})\\d{7}$")))
    {
        return true;
    }
    return false;
}

bool RegexValidation::isDataOfBirthValid(const std::string& birthDate)
{
    std::regex pattern1("^(0?[1-9]|[1-2][0-9]|3[0-1])[\\/](0?[1-9]|1[0-2])[\\/](\\d{4})$");
    std::regex pattern2("^(0?[1-9]|[1-2][0-9]|3[0-1])\\.(0?[1-9]|1[0-2])\\.(\\d{4})$");
    if ((std::regex_match(birthDate, pattern1) || std::regex_match(birthDate, pattern2)))
    {
        return true;
    }
	return false;
}
