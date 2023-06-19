#pragma once
#define NOMIMMAX
#include "sqlite3.h"
#include "IDatabase.h"

#define ERROR_RESPONSE_CODE 1
#define FOUND_RESPONSE_CODE 2

class SqliteDatabase : public IDatabase
{
public:
	SqliteDatabase();
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
	sqlite3* _db;
	std::string _dbFileName;

	void fixValue(std::string& value);

	void addQuestionsToDatabase();
	int addQuestion(QuestionStruct& q);

	int addQuestion(UserQuestionStruct& q);

	bool createTables(int& res);
	static int callbackHighScores(void* list, int argc, char** argv, char** azColName);
	static int callbackString(void* list, int argc, char** argv, char** azColName);
	static int callbackQuestions(void* list, int argc, char** argv, char** azColName);
	static int callbackUserQuestions(void* list, int argc, char** argv, char** azColName);
};