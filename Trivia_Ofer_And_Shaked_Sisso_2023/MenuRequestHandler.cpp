#include "MenuRequestHandler.h"

#define FALSE 0
#define TRUE !FALSE


MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory, IDatabase* database, LoggedUser& user, RoomManager& roomManager, StatisticsManager& statisticsManager)
    : m_database(database), m_handlerFactory(handlerFactory), m_user(user), m_roomManager(roomManager), m_statisticsManager(statisticsManager)
{
}

bool MenuRequestHandler::isRequestRelevent(const RequestInfo& info)
{
    if (info.id == GetPlayersInRoom || info.id == JoinRoom || info.id == CreateRoom || info.id == HighScore
        || info.id == Logout || info.id == GetRooms || info.id == Statistics || info.id == AddQuestion)
    {
        return true;
    }
    return false;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& info)
{
    RequestResult result;
    try
    {
        if (isRequestRelevent(info))
        {
            switch (info.id)
            {
            case Logout:
                result = signout(info);
                break;
            case GetRooms:
                result = getRooms(info);
                break;
            case GetPlayersInRoom:
                result = getPlayersInRoom(info);
                break;
            case Statistics:
                result = getPersonalStats(info);
                break;
            case HighScore:
                result = getHighScore(info);
                break;
            case JoinRoom:
                result = joinRoom(info);
                break;
            case CreateRoom:
                result = createRoom(info);
                break;
            case AddQuestion:
                result = addQuestion(info);
                break;
            default:
                throw std::exception("irrelevent request");
                break;
            }
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        result.newHandler = this;
        ErrorResponse response;
        response.message = e.what();
        result.buffer = JsonResponsePacketSerializer::serializeResponse(response);
    }
    return result;
}

RequestResult MenuRequestHandler::signout(const RequestInfo& info)
{
    RequestResult result;
    try
    {
        LoginManager& manager = this->m_handlerFactory.getLoginManager();
        manager.logout(this->m_user.getUsename()); 
        result.newHandler = nullptr; //the client is signing out 
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
    LogoutResponse response;
    response.status = Logout;
    result.buffer = JsonResponsePacketSerializer::serializeResponse(response);
    return result;
}

RequestResult MenuRequestHandler::getRooms(const RequestInfo& info)
{
    RequestResult result;
    std::vector<RoomData> rooms;
    try
    {
        rooms = this->m_roomManager.getRooms();
        result.newHandler = (IRequestHandler*)(this);
    }
    catch (const std::exception& e)
    {
        result.newHandler = nullptr;
        throw std::exception(e.what());
    }
    GetRoomsResponse response;
    response.rooms = rooms;
    response.status = GetRooms;
    result.buffer = JsonResponsePacketSerializer::serializeResponse(response);
    return result;
}

RequestResult MenuRequestHandler::getPlayersInRoom(const RequestInfo& info)
{
    RequestResult result;
    std::vector<std::string> players;
    try
    {
        GetPlayersInRoomRequest request = JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(info.buffer);
        players = this->m_roomManager.getRoom(request.roomId).getAllUsers();
        result.newHandler = (IRequestHandler*)(this);
    }
    catch (const std::exception& e)
    {
        result.newHandler = nullptr;
        throw std::exception(e.what());
    }
    GetPlayersInRoomResponse response;
    response.players = players;
    result.buffer = JsonResponsePacketSerializer::serializeResponse(response);
    return result;
}

RequestResult MenuRequestHandler::getPersonalStats(const RequestInfo& info)
{
    RequestResult result;
    std::vector<std::string> stats;
    try
    {
        stats = this->m_statisticsManager.getUserStatistics(this->m_user.getUsename());
        result.newHandler = (IRequestHandler*)(this);
    }
    catch (const std::exception& e)
    {
        result.newHandler = nullptr;
        throw std::exception(e.what());
    }
    GetPersonalStatsResponse response;
    response.status = Statistics;
    response.statistics = stats;
    result.buffer = JsonResponsePacketSerializer::serializeResponse(response);
    return result;
}

RequestResult MenuRequestHandler::getHighScore(const RequestInfo& info)
{
    RequestResult result;
    std::vector<std::string> highScore;
    try
    {
        highScore = this->m_statisticsManager.getHighScore();
        result.newHandler = (IRequestHandler*)(this);
    }
    catch (const std::exception& e)
    {
        result.newHandler = nullptr;
        throw std::exception(e.what());
    }
    GetHighScoreResponse response;
    response.status = HighScore;
    response.statistics = highScore;
    result.buffer = JsonResponsePacketSerializer::serializeResponse(response);
    return result;
}

RequestResult MenuRequestHandler::joinRoom(const RequestInfo& info)
{
    RequestResult result;
    try
    {
        JoinRoomRequest request = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(info.buffer);
        Room* room = &this->m_roomManager.getRoom(request.roomId);
        room->addUser(this->m_user);
        result.newHandler = (IRequestHandler*)this->m_handlerFactory.createRoomMemberRequestHandler(this->m_user, room);
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
    JoinRoomResponse response;
    response.status = JoinRoom;
    result.buffer = JsonResponsePacketSerializer::serializeResponse(response);
    return result;
}

RequestResult MenuRequestHandler::createRoom(const RequestInfo& info)
{
    RequestResult result;
    unsigned int id = 0;
    try
    {
        CreateRoomRequest request = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(info.buffer);
        id = this->m_roomManager.getRooms().size() + 1;
        RoomData data = { id, request.roomName, request.maxUsers, request.questionCount, request.answerTimeout, FALSE };
        this->m_roomManager.createRoom(this->m_user, data, request.includeUserQuestion);
        result.newHandler = (IRequestHandler*)this->m_handlerFactory.createRoomAdminRequestHandler(this->m_user, &this->m_roomManager.getRoom(id));
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
    CreateRoomResponse response;
    response.status = CreateRoom;
    result.buffer = JsonResponsePacketSerializer::serializeResponse(response);
    return result;
}

RequestResult MenuRequestHandler::addQuestion(const RequestInfo& info)
{
    RequestResult result;
    try
    {
        AddQuestionRequest request = JsonRequestPacketDeserializer::deserializeAddQuestionRequest(info.buffer);
        this->m_database->addUserQuestion(request.author, request.question, request.correctAnswer, request.ans2, request.ans3, request.ans4);
        result.newHandler = (IRequestHandler*)this;
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
    AddQuestionResponse response;
    response.status = AddQuestion;
    result.buffer = JsonResponsePacketSerializer::serializeResponse(response);
    return result;
}
