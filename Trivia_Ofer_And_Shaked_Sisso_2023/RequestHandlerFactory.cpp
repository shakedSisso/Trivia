#include "RequestHandlerFactory.h"

int RequestHandlerFactory::instanceCount = 0;

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database)
    : m_database(database), m_loginManager(database)
{
    if (instanceCount != 0)
    {
        throw std::exception("Request handler factory was already created once.");
    }
    instanceCount++;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    return new LoginRequestHandler(*this);
}

LoginManager* RequestHandlerFactory::getLoginManager()
{
    return &this->m_loginManager;
}

void RequestHandlerFactory::setDatabase(IDatabase* db)
{
    this->m_database = db;
    this->m_loginManager.setDatabase(db);
}
