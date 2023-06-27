#pragma once
#include <iostream>

class ApiEntity
{
public:
    /*
    * Function: static checkForHtmlEntity
    * ----------------------------
    *   The function gets a refernce to a string and calls replacehtmlEntity in order to replace all HTML symbols for unique symbols and normalize the string.
    *
    *   std::string& str: The string to replace the symbols in
    *
    *   returns: void.
    */
	static void checkForHtmlEntity(std::string& str);
private:
    /*
    * Function: static replaceHtmlEntity
    * ----------------------------
    *   The function gets a refernce to a string, an HTML entity (a group of letters that represent a special symbol) and the symbol to replace it with. The function goes over the string and replaces all the entities with the given replacement.
    *
    *   std::string& str: The string to replace the symbols in
    *   std::string& entity: The HTML entity to replace
    *   std::string& replacement: The symbol to replace the entity
    *
    *   returns: void.
    */
	static void replaceHtmlEntity(std::string& str, const std::string& entity, const std::string& replacement);
};