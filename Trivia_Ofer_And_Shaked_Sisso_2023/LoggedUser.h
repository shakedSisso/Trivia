#pragma once
#include <iostream>

class LoggedUser
{
public:
	LoggedUser(const std::string username);
	std::string getUsename() const;

    /*
    * Function: operator<
    * ----------------------------
    *   The function gets a reference to a Logged user and the function returns true if this given Logged user is has higher alphabetical value then the called Logged user object and false otherwise.
    *   This function was added to the class in order to be able to use this class as a key in an ordered map
    *
    *   const LoggedUser& other: the other Logged user to compare to called object to
    *
    *   returns: bool. True if the given LoggedUser has higher alphabetical value and false otherwise
    */
	bool operator<(const LoggedUser& other) const;
private:
	std::string m_username;
};