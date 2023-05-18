#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <list>

#define FILENAME "autoQuestions.txt"
#define FILE_NOT_OPEN -999

typedef struct Question
{
	int id;
	std::string question;
	std::string correct_ans;
	std::string ans2;
	std::string ans3;
	std::string ans4;
}Question;

class AutoQuestions
{
public :
	static std::list<Question> getQuestionsFromFile();
};