#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include <exception>

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory, LoginManager& loginManager)
    : m_handlerFactory(handlerFactory), m_loginManager(loginManager)
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
    RequestResult result;
    try
    {
        LoginRequest login = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
        this->m_loginManager.login(login.username, login.password);
        LoggedUser user(login.username);
        result.newHandler = (IRequestHandler*)this->m_handlerFactory.createMenuRequestHandler(user);
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
    LoginResponse response;
    response.status = Login;
    result.buffer = JsonResponsePacketSerializer::serializeResponse(response);
    return result;
}

RequestResult LoginRequestHandler::signup(const RequestInfo& info)
{
    LoginManager manager = this->m_handlerFactory.getLoginManager();
    RequestResult result;
    try
    {
        SignupRequest signUp = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);
        this->m_loginManager.signup(signUp.username, signUp.password, signUp.email, signUp.address, signUp.phoneNumber, signUp.birthDate);
        LoggedUser user(signUp.username);
        result.newHandler = (IRequestHandler*)this->m_handlerFactory.createMenuRequestHandler(user);

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
    SignupResponse response;
    response.status = Signup;
    result.buffer = JsonResponsePacketSerializer::serializeResponse(response);
    return result;
}
