#pragma once
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/oid.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/database.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/write_concern.hpp>


#include "IDatabase.h"
#include "json.hpp"

using json = nlohmann::json;


#define ERROR_RESPONSE_CODE 1
#define FOUND_RESPONSE_CODE 2

class MongoDatabase : public IDatabase
{
public:
	MongoDatabase();
	bool open() override;
	bool close() override;
	int doesUserExist(const std::string username) override;
	int doesPasswordMatch(const std::string username, const std::string password) override;
	int addNewUser(const std::string username, const std::string password, const std::string mail, const std::string address, const std::string phoneNumber, const std::string birthDate) override;
	std::list<Question> getQuestions(const int amountOfQuestions) override;
	float getPlayerAverageAnswerTime(const std::string username) override;
	int getNumOfCorrectAnswers(const std::string username) override;
	int getNumOfTotalAnswers(const std::string username) override;
	int getNumOfPlayerGames(const std::string username) override;
	int getPlayerScore(const std::string username) override;
	std::vector<std::string> getHighScores() override;
	int submitGameStatistics(const std::string username, const int correctAnswerCount, const int wrongAnswerCount, const float averageAnswerTime) override;
private:
	mongocxx::uri _uri;
	mongocxx::client _client;
	mongocxx::database _db;

	void addQuestionsToDatabase();
	int addQuestion(const QuestionStruct& q);

	json getUserStatisticsJson(const std::string& username);
};