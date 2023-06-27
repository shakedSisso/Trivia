#pragma once
#include "IDatabase.h"
#include <vector>
#include <string>

using std::string;
using std::vector;

class StatisticsManager
{
public:
	StatisticsManager(IDatabase* database);
	vector<string> getHighScore() const;
	vector<string> getUserStatistics(const string username) const;
	/*
	* Function: setDatabase
	* ----------------------------
	*   The function gets a pointer to an IDatabase object and sets the m_database pointer to the given pointer
	*
	*   IDatabase* database: The new pointer to the database to set
	*
	*   returns: void.
	*/
	void setDatabase(IDatabase* database);

private:
	IDatabase* m_database;
};