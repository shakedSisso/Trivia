#include "Game.h"

#define START_INDEX 0
#define DEFAULT_VALUE 999

Game::Game() : m_database(nullptr), m_questions(), m_gameId(DEFAULT_VALUE), m_gameSettings(RoomData()), m_players()
{
}

Game::Game(IDatabase* database, vector<Question> questions, vector<LoggedUser> users, const Room& room)
    :m_database(database), m_gameId(room.getRoomData().id), m_gameSettings(room.getRoomData())
{
    for (auto& question : questions)
    {
        this->m_questions.push_back(question);
    }
    for (auto user : users)
    {
        GameData* gameData = new GameData();
        gameData->currentQuestion = m_questions[START_INDEX];
        this->m_players.insert({ user, gameData });
        
    }
}

Question Game::getQuestionForUser(const LoggedUser& user)
{
    GameData* gameData = nullptr;
    for (auto player : this->m_players)
    {
        if (player.first.getUsename() == user.getUsename())
        {
            gameData = player.second;
        }
    }
    Question question;
    if (gameData != nullptr)
    {
        question = gameData->currentQuestion;
    }
    return question;
}

int Game::submitAnswer(const LoggedUser& user, int answerId, int answeringTime)
{
    GameData* gameData = this->m_players[user];
    int questionCount = gameData->correctAnswerCount + gameData->wrongAnswerCount;
    gameData->averageAnswerTime = (gameData->averageAnswerTime * questionCount + answeringTime) / (questionCount + 1);
    int correctAnswerId = gameData->currentQuestion.getCorrectAnswerId();
    if (correctAnswerId == answerId)
    {
        gameData->correctAnswerCount++;
    }
    else
    {
        gameData->wrongAnswerCount++;
    }
    if (gameData->correctAnswerCount + gameData->wrongAnswerCount >= this->m_questions.size()) // checking if this is last question in the game, if it is will set the next question to an empty one so that we'll know that the user finished his questions
    {
        gameData->currentQuestion = Question();
    }
    else
    {
        gameData->currentQuestion = this->m_questions[gameData->correctAnswerCount + gameData->wrongAnswerCount]; // setting the next question for the user in his gameData struct
    }
    return correctAnswerId;
}

void Game::removePlayer(const LoggedUser& user)
{
    auto player = this->m_players.find(user);
    this->m_database->submitGameStatistics(player->first.getUsename(), player->second->correctAnswerCount, player->second->wrongAnswerCount, player->second->averageAnswerTime);
    GameData* gameData = this->m_players[user];
    gameData->currentQuestion = Question(LOG_OUT,vector<string>(), -999); //users don't get removed with erase, so we use this to mark user's log out
}

GameID Game::getGameId() const
{
    return this->m_gameId;
}

map<LoggedUser, GameData*> Game::getPlayers() const
{
    return this->m_players;
}

bool Game::isGameFinished() const
{
    bool isFinished = true;
    for (auto player = this->m_players.begin(); player != this->m_players.end(); player++)
    {
        if (player->second->currentQuestion.getQuestion() != LOG_OUT && player->second->currentQuestion.getQuestion() != "") // if there is a user with a currect question that the question text is not empty then the game is not finished
        {
            isFinished = false;
            break;
        }
    }
    return isFinished;
}

bool Game::areAllPlayersLoggedOut() const
{
    bool allLoggedOut = true;
    for (auto player = this->m_players.begin(); player != this->m_players.end(); player++)
    {
        if (player->second->currentQuestion.getQuestion() != LOG_OUT)
        {
            allLoggedOut = false;
            break;
        }
    }
    return allLoggedOut;
}
