#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include "Globals.h"

#define FILENAME "autoQuestions.txt"
#define FILE_NOT_OPEN -999

class AutoQuestions
{
public :
	static std::list<Question> getQuestionsFromFile();
};