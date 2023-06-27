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
	std::list<Question> getQuestions(const int amountOfQuestions, const bool includeUserQuestions) override;
	float getPlayerAverageAnswerTime(const std::string username) override;
	int getNumOfCorrectAnswers(const std::string username) override;
	int getNumOfTotalAnswers(const std::string username) override;
	int getNumOfPlayerGames(const std::string username) override;
	int getPlayerScore(const std::string username) override;
	std::vector<std::string> getHighScores() override;
	int submitGameStatistics(const std::string username, const int correctAnswerCount, const int wrongAnswerCount, const float averageAnswerTime) override;
	int addUserQuestion(const std::string author, const std::string question, const std::string correctAnswer, const std::string ans2, const std::string ans3, const std::string ans4) override;
private:
	mongocxx::uri _uri;
	mongocxx::client _client;
	mongocxx::database _db;

	/*
	* Function: addQuestionToDatabase
	* ----------------------------
	*   The function uses curl and gets questions from the API and inserts them to the database
	*
	*   input: none
	*
	*   returns: void.
	*/
	void addQuestionsToDatabase();
	/*
	* Function: addQuestion
	* ----------------------------
	*   The function gets a QuestionStruct refernce and inserts the question to the database in the question collection
	*
	*   const QuestionStruct& q: The refernce to the question to add
	*
	*   returns: int.
	*/
	int addQuestion(const QuestionStruct& q);

	/*
	* Function: addUserQuestion
	* ----------------------------
	*   The function gets a UserQuestionStruct refernce and inserts the question to the database in the user questions collection
	*
	*   const QuestionStruct& q: The refernce to the question to add
	*
	*   returns: int.
	*/
	int addUserQuestion(const UserQuestionStruct& q);

	/*
	* Function: getUserStatisticsJson
	* ----------------------------
	*   The function gets a username and the function returns a json object with the user's stats
	*
	*   const std::string& username: the string of the user to get the stats for
	*
	*   returns: json. The json object of the user's stats
	*/
	json getUserStatisticsJson(const std::string& username);
};