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
	void setDatabase(IDatabase* database);

private:
	IDatabase* m_database;
};