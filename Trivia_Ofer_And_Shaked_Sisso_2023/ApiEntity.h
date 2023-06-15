#pragma once
#include <iostream>

class ApiEntity
{
public:
	static void checkForHtmlEntity(std::string& str);
private:
	static void replaceHtmlEntity(std::string& str, const std::string& entity, const std::string& replacement);
};