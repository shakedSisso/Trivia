#include "Game.h"

Game::Game(vector<Question> questions, vector<LoggedUser> users, const Room& room)
    : m_questions(questions), m_gameId(room.getRoomData().id), m_gameSettings(room.getRoomData())
{
    for (auto user = users.begin(); user != users.end(); user++)
    {
        GameData gameData;
        this->m_players[*user] = gameData;
        
    }
}

Question Game::getQuestionForUser(const LoggedUser& user) const
{
    return this->m_players.at(user).currentQuestion;
}

int Game::submitAnswer(const LoggedUser& user, int answerId)
{
    int correctAnswerId = this->m_players[user].currentQuestion.getCorrectAnswerId();
    if (correctAnswerId == answerId)
    {
        this->m_players[user].correctAnswerCount++;
    }
    else
    {
        this->m_players[user].wrongAnswerCount++;
    }
    if (this->m_players[user].correctAnswerCount + this->m_players[user].wrongAnswerCount >= this->m_questions.size()) // checking if this is last question in the game, if it is will set the next question to an empty one so that we'll know that the user finished his questions
    {
        this->m_players[user].currentQuestion = Question();
    }
    else
    {
        this->m_players[user].currentQuestion = this->m_questions[this->m_players[user].correctAnswerCount + this->m_players[user].wrongAnswerCount]; // setting the next question for the user in his gameData struct
    }
    return correctAnswerId;
}

void Game::removePlayer(const LoggedUser& user)
{
    this->m_players.erase(user);
}

GameID Game::getGameId() const
{
    return this->m_gameId;
}

map<LoggedUser, GameData> Game::getPlayers() const
{
    return this->m_players;
}

bool Game::isGameFinished() const
{
    bool isFinished = true;
    for (auto player = this->m_players.begin(); player != this->m_players.end() && isFinished; player++)
    {
        if (player->second.currentQuestion.getQuestion() != "") // if there is a user with a currect question that the question text is not empty then the game is not finished
        {
            isFinished = false;
        }
    }
    return isFinished;
}
