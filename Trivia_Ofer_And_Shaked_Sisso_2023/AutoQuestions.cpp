#include "AutoQuestions.h"


std::list<Question> AutoQuestions::getQuestionsFromFile()
{

	std::list<Question> questions;
	Question question;
	std::ifstream file(FILENAME);
	std::string line;
	int count = 0;

	if (!file.is_open())
	{
		question.id = FILE_NOT_OPEN;
		questions.push_back(question);
		return questions;
	}

	while (std::getline(file, line))
	{
		count++;
		question.id = count;
		// Read the four lines and store them in the struct fields
		question.question = line;
		if (std::getline(file, line))
			question.correct_ans = line;
		if (std::getline(file, line))
			question.ans2 = line;
		if (std::getline(file, line))
			question.ans3 = line;
		if (std::getline(file, line))
			question.ans4 = line;
		if (std::getline(file, line)) // for the empty line between the questions

			questions.push_back(question);
	}
	return questions;
}