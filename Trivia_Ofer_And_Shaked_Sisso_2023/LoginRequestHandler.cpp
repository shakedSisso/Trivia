#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include <exception>

#define RESPONSE_STATUS_LOGIN 1
#define RESPONSE_STATUS_SIGN_UP 2

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory)
    : m_handlerFactory(handlerFactory)
{
}

bool LoginRequestHandler::isRequestRelevent(const RequestInfo& info)
{
    if (info.id == LOGIN_REQUEST || info.id == SIGN_UP_REQUEST)
    {
        return true;
    }
    return false;
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& info)
{
    RequestResult result;
    try
    {
        if (isRequestRelevent(info))
        {
            if (info.id == SIGN_UP_REQUEST)
            {
                result = signup(info);
            }
            else
            {
                result = login(info);
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

RequestResult LoginRequestHandler::login(const RequestInfo& info)
{
    LoginManager* manager = this->m_handlerFactory.getLoginManager();
    RequestResult result;
    MenuRequestHandler* menuHandler = new MenuRequestHandler();
    result.newHandler = (IRequestHandler*)menuHandler;
    try
    {
        LoginRequest login = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
        manager->login(login.username, login.password);
    }
    catch (const std::exception& e)
    {
        throw std::exception(e.what());
    }
    LoginResponse response;
    response.status = RESPONSE_STATUS_LOGIN;
    result.buffer = JsonResponsePacketSerializer::serializeResponse(response);
    return result;
}

RequestResult LoginRequestHandler::signup(const RequestInfo& info)
{
    LoginManager* manager = this->m_handlerFactory.getLoginManager();
    RequestResult result;
    MenuRequestHandler* menuHandler = new MenuRequestHandler();
    result.newHandler = (IRequestHandler*)menuHandler;
    try
    {
        SignupRequest signUp = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);
        manager->signup(signUp.username, signUp.password, signUp.email);
    }
    catch (const std::exception& e)
    {
        throw std::exception(e.what());
    }
    SignupResponse response;
    response.status = RESPONSE_STATUS_SIGN_UP;
    result.buffer = JsonResponsePacketSerializer::serializeResponse(response);
    return result;
}
