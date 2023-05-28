#include "RequestHandlerFactory.h"

int RequestHandlerFactory::instanceCount = 0;

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database)
    : m_database(database), m_loginManager(database), m_roomManager(), m_statisticsManager(database)
{
    if (instanceCount != 0)
    {
        throw std::exception("Request handler factory was already created once.");
    }
    instanceCount++;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    return new LoginRequestHandler(*this, this->m_loginManager);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser& user)
{
    return new MenuRequestHandler(*this, user, this->m_roomManager, this->m_statisticsManager);
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return this->m_loginManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
    return this->m_roomManager;
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
    return this->m_statisticsManager;
}

void RequestHandlerFactory::setDatabase(IDatabase* db)
{
    this->m_database = db;
    this->m_loginManager.setDatabase(db);
    this->m_statisticsManager.setDatabase(db);
}
