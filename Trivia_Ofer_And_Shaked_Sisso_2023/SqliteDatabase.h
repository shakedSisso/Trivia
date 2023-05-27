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
	std::list<Question> getQuestions(int amountOfQuestions) override;
	float getPlayerAverageAnswerTime(std::string username) override;
	int getNumOfCorrectAnswers(std::string username) override;
	int getNumOfTotalAnswers(std::string username) override;
	int getNumOfPlayerGames(std::string username) override;
	int getPlayerScore(std::string username) override;
	std::vector<std::string> getHighScores() override;
private:
	sqlite3* _db;
	std::string _dbFileName;

	void addQuestionsToDatabase();
	int addQuestion(const QuestionStruct& q);

	bool createTables(int& res);
	static int callbackString(void* list, int argc, char** argv, char** azColName);
	static int callbackQuestions(void* list, int argc, char** argv, char** azColName);
};