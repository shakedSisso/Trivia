#include "MenuRequestHandler.h"

#define FALSE 0
#define TRUE !FALSE

#define HEAD_TO_HEAD_DOES_NOT_EXIST -999
#define HEAD_TO_HEAD_ROOM_NAME "HeadToHead"
#define HEAD_TO_HEAD_MAX_PLAYERS 2
#define HEAD_TO_HEAD_QUESTION_COUNT 15
#define HEAD_TO_HEAD_QUESTION_TIME_OUT 10

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory, IDatabase* database, LoggedUser& user, RoomManager& roomManager, StatisticsManager& statisticsManager)
    : m_database(database), m_handlerFactory(handlerFactory), m_user(user), m_roomManager(roomManager), m_statisticsManager(statisticsManager)
{
}

bool MenuRequestHandler::isRequestRelevent(const RequestInfo& info)
{
    if (info.id == GetPlayersInRoom || info.id == JoinRoom || info.id == CreateRoom || info.id == HighScore
        || info.id == Logout || info.id == GetRooms || info.id == Statistics || info.id == AddQuestion || info.id == HeadToHead)
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
            case HeadToHead:
                result = joinHeadToHead(info);
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
        removeHeadToHeadRoomsFromTheList(rooms);
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

RequestResult MenuRequestHandler::joinHeadToHead(const RequestInfo& info)
{
    RequestResult result;
    unsigned int id = 0;
    Room* room = nullptr;
    try
    {
        std::vector<RoomData> rooms = this->m_roomManager.getRooms();
        id = findHeadToHeadRoom(rooms);
        if (id == HEAD_TO_HEAD_DOES_NOT_EXIST)
        {
            id = rooms.size() + 1;
            RoomData data = { id, HEAD_TO_HEAD_ROOM_NAME, HEAD_TO_HEAD_MAX_PLAYERS, HEAD_TO_HEAD_QUESTION_COUNT, HEAD_TO_HEAD_QUESTION_TIME_OUT, FALSE, TRUE };
            this->m_roomManager.createRoom(this->m_user, data, FALSE);
            room = &this->m_roomManager.getRoom(id);
            result.newHandler = (IRequestHandler*)this->m_handlerFactory.createRoomMemberRequestHandler(this->m_user, room);
        }
        else
        {
            room = &this->m_roomManager.getRoom(id);
            room->addUser(this->m_user);
            room->activate(); //head to head rooms needs to be activated when there are 2 users in the room
            result.newHandler = (IRequestHandler*)this->m_handlerFactory.createRoomMemberRequestHandler(this->m_user, room);
            this->m_handlerFactory.getGameManager().createGame(*room); //creating the head to head game
        }
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
    HeadToHeadResponse response;
    response.status = HeadToHead;
    result.buffer = JsonResponsePacketSerializer::serializeResponse(response);
    return result;
}

void MenuRequestHandler::removeHeadToHeadRoomsFromTheList(std::vector<RoomData>& rooms)
{
    for (auto it = rooms.begin(); it != rooms.end(); ) 
    {
        if ((*it).isDuo) 
        {
            it = rooms.erase(it); // Remove the element and advance the iterator
        }
        else 
        {
            ++it; // Move to the next element
        }
    }
}

int MenuRequestHandler::findHeadToHeadRoom(std::vector<RoomData> rooms) const
{
    for (auto room : rooms)
    {
        if (room.name == HEAD_TO_HEAD_ROOM_NAME && !room.isActive)
        {
            return room.id;
        }
    }
    return HEAD_TO_HEAD_DOES_NOT_EXIST;
}
