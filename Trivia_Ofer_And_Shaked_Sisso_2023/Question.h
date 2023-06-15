#pragma once 
#include <iostream>
#include <vector>

class Question
{
public:
	Question(const std::string question, const std::vector<std::string> answers, int correctAnsId);
	Question();
	std::string getQuestion() const;
	std::vector<std::string> getPossibleAnswers() const;
	int getCorrectAnswerId() const;
	Question& operator=(const Question& other);
private:
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;
	int m_correctAnswerId;
};