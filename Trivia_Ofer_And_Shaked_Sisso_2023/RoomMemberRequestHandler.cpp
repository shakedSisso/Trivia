#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, Room* room, LoggedUser& user, RoomManager& roomManager)
    : m_room(room), m_user(user), m_handlerFactory(handlerFactory), m_roomManager(roomManager), m_roomId(m_room->getRoomData().id)
{
}

bool RoomMemberRequestHandler::isRequestRelevent(const RequestInfo& info)
{
    if (info.id == LeaveRoom || info.id == StartGame || info.id == GetRoomState)
    {
        return true;
    }
    return false;
}

RequestResult RoomMemberRequestHandler::handleRequest(const RequestInfo& info)
{
    RequestResult result;
    try
    {
        if (isRequestRelevent(info))
        {
            switch (info.id)
            {
            case LeaveRoom:
                result = leaveRoom(info);
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

RequestResult RoomMemberRequestHandler::leaveRoom(const RequestInfo& info)
{
    RequestResult result;
    try
    {
        this->m_roomManager.getRoom(this->m_roomId); // checking if the room still exists and that the room admin hasn't closed it
    }
    catch (const std::exception& e)
    {
        result.newHandler = (IRequestHandler*)this->m_handlerFactory.createMenuRequestHandler(this->m_user); // if the room has been closed we we'll divert the room memeber back to the menu
    }
    if (result.newHandler == nullptr) // if the room exists the newHandler won't be filled (no exception will be raised)
    {
        try
        {
            this->m_room->removeUser(this->m_user);
            result.newHandler = (IRequestHandler*)this->m_handlerFactory.createMenuRequestHandler(this->m_user);
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
    }
    LeaveRoomResponse response;
    response.status = LeaveRoom;
    result.buffer = JsonResponsePacketSerializer::serializeResponse(response);
    return result;
}

RequestResult RoomMemberRequestHandler::getRoomState(const RequestInfo& info)
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

RequestResult RoomMemberRequestHandler::startGame(const RequestInfo& info)
{
    RequestResult result;
    try
    {
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