#include "Question.h"

Question::Question(const std::string question, const std::vector<std::string> answers, int correctAnsId)
    : m_question(question), m_possibleAnswers(answers), m_correctAnswerId(correctAnsId)
{
}

std::string Question::getQuestion() const
{
    return this->m_question;
}

std::vector<std::string> Question::getPossibleAnswers() const
{
    return this->m_possibleAnswers;
}

int Question::getCorrectAnswerId() const
{
    return this->m_correctAnswerId;
}
