#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <list>

#define FILENAME "autoQuestions.txt"
#define FILE_NOT_OPEN -999

typedef struct QuestionStruct
{
	int id;
	int correctAnsId;
	std::string question;
	std::string ans1;
	std::string ans2;
	std::string ans3;
	std::string ans4;
}QuestionStruct;

class AutoQuestions
{
public :
	static std::list<QuestionStruct> getQuestionsFromFile();
};