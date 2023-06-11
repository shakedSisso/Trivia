#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, Room* room, LoggedUser& user, RoomManager& roomManager)
    : m_room(room), m_user(user), m_handlerFactory(handlerFactory), m_roomManager(roomManager)
{
}

bool RoomAdminRequestHandler::isRequestRelevent(const RequestInfo& info)
{
    if (info.id == CloseRoom || info.id == StartGame || info.id == GetRoomState)
    {
        return true;
    }
    return false;
}

RequestResult RoomAdminRequestHandler::handleRequest(const RequestInfo& info)
{
    RequestResult result;
    try
    {
        if (isRequestRelevent(info))
        {
            switch (info.id)
            {
            case CloseRoom:
                result = closeRoom(info);
                break;
            case StartGame:
                result = startGame(info);
                break;
            case GetRoomState:
                result = getRoomState(info);
                break;
            default:
                throw std::exception("irrelevent request");
                break;
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

RequestResult RoomAdminRequestHandler::closeRoom(const RequestInfo& info)
{
    RequestResult result;
    try
    {
        this->m_handlerFactory.getRoomManager().deleteRoom(this->m_room->getRoomData().id);
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
    CloseRoomResponse response;
    response.status = CloseRoom;
    result.buffer = JsonResponsePacketSerializer::serializeResponse(response);
    return result;
}

RequestResult RoomAdminRequestHandler::startGame(const RequestInfo& info)
{
    RequestResult result;
    try
    {
        this->m_room->activate();
        result.newHandler = this->m_handlerFactory.createGameRequestHandler(this->m_user, *this->m_room);
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
    StartGameResponse response;
    response.status = StartGame;
    result.buffer = JsonResponsePacketSerializer::serializeResponse(response);
    return result;
}

RequestResult RoomAdminRequestHandler::getRoomState(const RequestInfo& info)
{
    RequestResult result;
    GetRoomStateResponse response;
    response.status = GetRoomState;
    try
    {
        RoomData data = this->m_room->getRoomData();
        response.players = this->m_room->getAllUsers();
        response.questionCount = data.numOfQuestionsInGame;
        response.answerTimeout = data.timePerQuestion;
        response.hasGameBegun = data.isActive;
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
    result.buffer = JsonResponsePacketSerializer::serializeResponse(response);
    return result;
}