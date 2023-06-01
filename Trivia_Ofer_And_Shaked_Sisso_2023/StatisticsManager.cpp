#include "StatisticsManager.h"
#include <iostream>
#include <sstream>
#include <string>

#define DIGITS_AFTER_POINT 3

StatisticsManager::StatisticsManager(IDatabase* database)
    : m_database(database)
{

}

vector<string> StatisticsManager::getHighScore() const
{
    return this->m_database->getHighScores();
}

vector<string> StatisticsManager::getUserStatistics(const string username) const
{
    vector<string> stats;
    int correctAnswers = 0;
    correctAnswers = this->m_database->getNumOfCorrectAnswers(username);

    std::stringstream stream;
    stream.precision(DIGITS_AFTER_POINT); // Set precision to the amount of digits after the decimal point the define has
    stream << std::fixed << this->m_database->getPlayerAverageAnswerTime(username); // Convert the number to string with fixed-point notation

    stats.push_back(stream.str());
    stats.push_back(std::to_string(correctAnswers));
    stats.push_back(std::to_string(this->m_database->getNumOfTotalAnswers(username) - correctAnswers));
    stats.push_back(std::to_string(this->m_database->getNumOfPlayerGames(username)));
    
    return stats;
}

void StatisticsManager::setDatabase(IDatabase* database)
{
    this->m_database = database;
}
