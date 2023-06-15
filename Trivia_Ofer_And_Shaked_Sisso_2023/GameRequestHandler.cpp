#include "GameRequestHandler.h"

GameRequestHandler::GameRequestHandler(RequestHandlerFactory& handlerFactory, GameManager& gameManager, GameID gameId, LoggedUser& user)
	: m_handlerFactory(handlerFactory), m_gameManager(gameManager), m_user(user)
{
    this->m_game = this->m_gameManager.getGame(gameId);
}

bool GameRequestHandler::isRequestRelevent(const RequestInfo& info)
{
	if (info.id == LeaveGame || info.id == GetQuestion || info.id == SubmitAnswer || info.id == GetGameResult)
	{
		return true;
	}
	return false;
}

RequestResult GameRequestHandler::handleRequest(const RequestInfo& info)
{
	RequestResult result;
    try
    {
        if (isRequestRelevent(info))
        {
            switch (info.id)
            {
            case LeaveGame:
                result = leaveGame(info);
                break;
            case GetQuestion:
                result = getQuestion(info);
                break;
            case SubmitAnswer:
                result = submitAnswer(info);
                break;
            case GetGameResult:
                result = getGameResults(info);
                break;
            default:
                throw std::exception("irrelevent request");
            }
        }
        else
        {
            throw std::exception("irrelevent request");
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        result.newHandler = this;
        ErrorResponse response;
        response.message = e.what();
        result.buffer = JsonResponsePacketSerializer::serializeResponse(response);
    }
	return result;
}

RequestResult GameRequestHandler::getQuestion(const RequestInfo& info)
{
    RequestResult result; 
    GetQuestionResponse response;
    try
    {
        Question question = this->m_game.getQuestionForUser(this->m_user);
        result.newHandler = (IRequestHandler*)(this);
        response.question = question.getQuestion();
        std::map<unsigned int, std::string> answers;
        if (response.question != "")
        {
            response.status = GetQuestion;
            std::vector<std::string> possibleAnswers = question.getPossibleAnswers();
            int count = 1;
            for (auto answer : possibleAnswers)
            {
                answers[count] = answer;
                count++;
            }
        }
        else
        {
            response.status = GetQuestionFailed;
        }
        response.answers = answers;
    }
    catch (const std::exception& e)
    {
        if (result.newHandler != nullptr)
        {
            delete(result.newHandler);
        }
        result.newHandler = nullptr;
        LoginManager& loginManager = m_handlerFactory.getLoginManager();
        loginManager.logout(this->m_user.getUsename());
        throw std::exception(e.what());
    }
    result.buffer = JsonResponsePacketSerializer::serializeResponse(response);
    return result;
}

RequestResult GameRequestHandler::submitAnswer(const RequestInfo& info)
{
    RequestResult result;
    int correctAnswerId = 0;
    try
    {
        SubmitAnswerRequest request = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(info.buffer);
        correctAnswerId = this->m_game.submitAnswer(this->m_user, request.answerId, request.answerTime);
        result.newHandler = (IRequestHandler*)(this);
    }
    catch (const std::exception& e)
    {
        if (result.newHandler != nullptr)
        {
            delete(result.newHandler);
        }
        result.newHandler = nullptr;
        LoginManager& loginManager = m_handlerFactory.getLoginManager();
        loginManager.logout(this->m_user.getUsename());
        throw std::exception(e.what());
    }
    SubmitAnswerResponse response;
    response.status = SubmitAnswer;
    response.correctAnswerId = correctAnswerId;
    result.buffer = JsonResponsePacketSerializer::serializeResponse(response);
    return result;
}

RequestResult GameRequestHandler::getGameResults(const RequestInfo& info)
{
    RequestResult result;
    std::vector<PlayerResults> results;
    GetGameResultsResponse response;
    try
    {
        PlayerResults player;
        GameData gameData;
        if (this->m_game.isGameFinished())
        {
            response.status = GetGameResult;
            std::map<LoggedUser, GameData*> players = this->m_game.getPlayers();
            for (auto it = players.begin(); it != players.end(); ++it)
            {
                gameData = *it->second;
                player.username = it->first.getUsename();
                player.correctAnswerCount = gameData.correctAnswerCount;
                player.wrongAnswerCount = gameData.wrongAnswerCount;
                player.averageAnswerTime = gameData.averageAnswerTime;
                results.push_back(player);
            }
        }
        else
        {
            response.status = GetGameResultFailed;
        }
        result.newHandler = (IRequestHandler*)(this);
    }
    catch (const std::exception& e)
    {
        if (result.newHandler != nullptr)
        {
            delete(result.newHandler);
        }
        result.newHandler = nullptr;
        LoginManager& loginManager = m_handlerFactory.getLoginManager();
        loginManager.logout(this->m_user.getUsename());
        throw std::exception(e.what());
    }
    response.results = results;
    result.buffer = JsonResponsePacketSerializer::serializeResponse(response);
    return result;
}

RequestResult GameRequestHandler::leaveGame(const RequestInfo& info)
{
    RequestResult result;
    try
    {
        this->m_game.removePlayer(this->m_user);
        if (this->m_game.getPlayers().empty())
        {
            GameManager& gameManager = this->m_handlerFactory.getGameManager();
            gameManager.deleteGame(this->m_game.getGameId());
        }
        result.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
    }
    catch (const std::exception& e)
    {
        if (result.newHandler != nullptr)
        {
            delete(result.newHandler);
        }
        result.newHandler = nullptr;
        throw std::exception(e.what());
    }
    LeaveGameResponse response;
    response.status = LeaveGame;
    result.buffer = JsonResponsePacketSerializer::serializeResponse(response);
    return result;
}