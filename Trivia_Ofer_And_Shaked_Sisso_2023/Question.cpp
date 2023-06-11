#include "Question.h"

enum answerId { ans1 = 1, ans2, ans3, ans4 };

Question::Question(const std::string question, const std::vector<std::string> answers, int correctAnsId)
    : m_question(question), m_correctAnswerId(correctAnsId)
{
    switch (correctAnsId)
    {
    case ans1:
        m_possibleAnswers = answers; //the correct answer is automatically the first answer
        break;
    case ans2:
        m_possibleAnswers = { answers[1], answers[0], answers[2], answers[3] };
        break;
    case ans3:
        m_possibleAnswers = { answers[1], answers[2], answers[0], answers[3] };
        break;
    case ans4:
        m_possibleAnswers = { answers[1], answers[2], answers[3], answers[0] };
        break;
    default:
        break;
    }
}

Question::Question()
    : m_question("")
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
