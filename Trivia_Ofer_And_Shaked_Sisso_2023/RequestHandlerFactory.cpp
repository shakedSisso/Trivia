#include "RequestHandlerFactory.h"

int RequestHandlerFactory::instanceCount = 0;

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database)
    : m_database(database), m_loginManager(database), m_roomManager(), m_statisticsManager(database), m_gameManager(database)
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

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser& user, Room* room)
{
    return new RoomAdminRequestHandler(*this, room, user, this->m_roomManager);
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser& user, Room* room)
{
    return new RoomMemberRequestHandler(*this, room, user, this->m_roomManager);
}

GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(LoggedUser& user, Room& room, GameID gameId)
{
    return new GameRequestHandler(*this, this->m_gameManager, gameId, user);
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

GameManager& RequestHandlerFactory::getGameManager()
{
    return this->m_gameManager;
}

void RequestHandlerFactory::setDatabase(IDatabase* db)
{
    this->m_database = db;
    this->m_loginManager.setDatabase(db);
    this->m_statisticsManager.setDatabase(db);
    this->m_gameManager.setDatabase(db);
}

IDatabase* RequestHandlerFactory::getDatabase()
{
    return this->m_database;
}
