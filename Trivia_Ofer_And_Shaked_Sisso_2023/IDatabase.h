#pragma once
#include <iostream>
#include "Question.h"
#include <list>
#include <vector>

#define HIGH_SCORES_COUNT 3

class IDatabase
{
public:
	IDatabase();
	virtual bool open() = 0;
	virtual bool close() = 0;
	virtual int doesUserExist(const std::string username) = 0;
	virtual int doesPasswordMatch(const std::string username, const std::string password) = 0;
	virtual int addNewUser(const std::string username, const std::string password, const std::string mail, const std::string address, const std::string phoneNumber, const std::string birthDate) = 0;
	virtual std::list<Question> getQuestions(int amountOfQuestions) = 0;
	virtual float getPlayerAverageAnswerTime(std::string username) = 0;
	virtual int getNumOfCorrectAnswers(std::string username) = 0;
	virtual int getNumOfPlayerGames(std::string username) = 0;
	virtual int getPlayerScore(std::string username) = 0;
	virtual std::vector<std::string> getHighScores() = 0;
private:
	static int instanceCount;
};