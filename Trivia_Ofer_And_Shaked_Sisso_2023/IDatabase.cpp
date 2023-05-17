#include "IDatabase.h"

int IDatabase::instanceCount = 0;

IDatabase::IDatabase()
{
	if (instanceCount != 0)
	{
		throw std::exception("A database was already created once.");
	}
	instanceCount++;
}
