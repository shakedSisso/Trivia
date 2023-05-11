#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include <exception>

#define RESPONSE_STATUS_LOGIN 1
#define RESPONSE_STATUS_SIGN_UP 2

bool LoginRequestHandler::isRequestRelevent(RequestInfo info)
{
    if (info.id == LOGIN_REQUEST || info.id == SIGN_UP_REQUEST)
    {
        return true;
    }
    return false;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info)
{
    RequestResult result;
    Buffer buffer;
    try {
        if (isRequestRelevent(info))
        {
            MenuRequestHandler* menuHandler = new MenuRequestHandler();
            result.newHandler = (IRequestHandler*)menuHandler;
            if (info.id == SIGN_UP_REQUEST)
            {
                SignupRequest signUp = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);
                SignupResponse response;
                response.status = RESPONSE_STATUS_SIGN_UP;
                buffer = JsonResponsePacketSerializer::serializeResponse(response);
            }
            else
            {
                LoginRequest login = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
                LoginResponse response;
                response.status = RESPONSE_STATUS_LOGIN;
                buffer = JsonResponsePacketSerializer::serializeResponse(response);
            }
        }
        else
        {
            throw std::exception("Request is irrelevent");
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        result.newHandler = this;
        ErrorResponse response;
        response.message = "ERROR";
        buffer = JsonResponsePacketSerializer::serializeResponse(response);
    }

    result.buffer = buffer;
    return result;
}
