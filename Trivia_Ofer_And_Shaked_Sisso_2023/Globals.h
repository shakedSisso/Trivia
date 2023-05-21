#pragma once
#include <vector>

using std::vector;

typedef int RequestId;
typedef unsigned char Byte;
typedef vector<Byte> Buffer;

typedef struct Question
{
	int id;
	std::string question;
	std::string correct_ans;
	std::string ans2;
	std::string ans3;
	std::string ans4;
}Question;
