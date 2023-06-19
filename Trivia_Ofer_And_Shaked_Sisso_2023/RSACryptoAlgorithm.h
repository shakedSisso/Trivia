#pragma once
#include "ICryptoAlgorithm.h"
#include <vector>

using std::vector;

class RSACryptoAlgorithm : public ICryptoAlgorithm
{
public:
	
	Buffer encrypt(const Buffer& message, const int& key, const int& modulus) override;
	Buffer decrypt(const Buffer& message) override;

private:
	Buffer EncryptBlock(const Buffer& block, const int& key, const int& modulus);
	Buffer DecryptBlock(const Buffer& block);
	int GetBlockSize();

	void createKeys(int keyLength);
	bool isPrime(int number);
	int getRandomPrime(int min, int max);
	int GCD(int a, int b);
	int ModInverse(int a, int m);
	int ModPow(int base, int exponent, int modulus);

	int m_publicKey;
	int m_privateKey;
	int m_modulus;
};