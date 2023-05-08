#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"

bool LoginRequestHandler::isRequestRelevent(RequestInfo info)
{
    if (info.id = LOGIN_REQUEST)
        return true;
    return false;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info)
{
    RequestResult result;
    result.buffer = info.buffer;
    if (isRequestRelevent(info))
    {
        MenuRequestHandler* menuHandler = new MenuRequestHandler();
        result.newHandler = (IRequestHandler*)menuHandler;
    }
    else
    {
        result.newHandler = this;
    }
    return result;
}
