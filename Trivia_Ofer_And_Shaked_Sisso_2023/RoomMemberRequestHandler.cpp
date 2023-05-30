#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, Room& room, LoggedUser& user, RoomManager& roomManager)
    :  m_room(room), m_user(user), m_handlerFactory(handlerFactory), m_roomManager(roomManager)
{
}

bool RoomAdminRequestHandler::isRequestRelevent(const RequestInfo& info)
{
    if (info.id == LeaveRoom || info.id == GetRoomState)
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
            if (info.id == LeaveRoom)
            {
                result = leaveRoom(info);
            }
            else
            {
                result = getRoomState(info);
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
        response.message = "ERROR";
        result.buffer = JsonResponsePacketSerializer::serializeResponse(response);
    }
    return result;
}

RequestResult RoomAdminRequestHandler::leaveRoom(const RequestInfo& info)
{
    RequestResult result;
    try
    {
        this->m_room.removeUser(this->m_user);
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
    LeaveRoomResponse response;
    response.status = LeaveRoom;
    result.buffer    = JsonResponsePacketSerializer::serializeResponse(response);
    return result;
}

RequestResult RoomAdminRequestHandler::getRoomState(const RequestInfo& info)
{
    RequestResult result;
    GetRoomStateResponse response;
    response.status = GetRoomState;
    try
    {
        RoomData data = this->m_room.getRoomData();
        response.players = this->m_room.getAllUsers();
        response.questionCount = data.numOfQuestionsInGame;
        response.answerTimeout == data.timePerQuestion;
        response.hasGameBegun = data.isActive;
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
