#pragma once
#include "ICryptoAlgorithm.h"
#include "IDatabase.h"
#include <vector>

using std::vector;

class RSACryptoAlgorithm : public ICryptoAlgorithm
{
public:
	RSACryptoAlgorithm(IDatabase* database);
	Buffer encrypt(const Buffer& message, const int& key, const int& modulus) override;
	Buffer decrypt(const Buffer& message) override;
	void setDatabase(IDatabase* database) override;
	void createKeys() override;
	std::vector<int> getKey() override;

private:

	void findKeys(long int phi, long int p, long int q);
	long int findPrivateKey(long int phi);
	bool isPrime(long int number);
	int getRandomPrime(int min, int max); 
	long int ModPow(int base, int exponent, int modulus);

	IDatabase* m_database;
	long int m_publicKey;
	long int m_privateKey;
	long int m_modulus;
};