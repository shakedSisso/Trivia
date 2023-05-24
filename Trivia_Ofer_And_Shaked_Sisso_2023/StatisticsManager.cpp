#include "StatisticsManager.h"

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

    stats.push_back(std::to_string(this->m_database->getPlayerAverageAnswerTime(username)));
    stats.push_back(std::to_string(correctAnswers));
    stats.push_back(std::to_string(this->m_database->getNumOfTotalAnswers(username) - correctAnswers));
    stats.push_back(std::to_string(this->m_database->getNumOfPlayerGames(username)));
    
}

void StatisticsManager::setDatabase(IDatabase* database)
{
    this->m_database = database;
}
