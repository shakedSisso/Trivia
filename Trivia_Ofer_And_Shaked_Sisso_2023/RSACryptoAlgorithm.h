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
	/*
	* Function: void findKeys(long int phi, long int p, long int q)
	* ----------------------------
	*	The function gets the phi, p and q and creates a public key and a private key
	*
	*	long int phi: the phi equals to (p-1)(q-1)
	*	long int p: one prime number
	*	long int q: second prime number
	*
	*	returns: long int.
   */
	void findKeys(long int phi, long int p, long int q);
	/*
	* Function: long int findPrivateKey(long int phi)
	* ----------------------------
	*	The function gets the phi and creates a private key
	*
	*	long int phi: the phi equals to (p-1)(q-1)
	*
	*	returns: long int.
   */
	long int findPrivateKey(long int phi);
	/*
	* Function: bool isPrime(long int number)
	* ----------------------------
	*	The function gets a number and checks if the number is a prime number
	*
	*	long int number: the number to check if prime
	*
	*	returns: bool.
   */
	bool isPrime(long int number);
	/*
	* Function: int getRandomPrime(int min, int max)
	* ----------------------------
	*	The function gets a minimum and maximum to create a range to get a prime number in the middle
	*
	*	int min: the lower end of the range
	*	int max: the uuper end of the range
	*
	*	returns: int.
   */
	int getRandomPrime(int min, int max); 
	/*
	* Function: long int ModPow(int base, int exponent, int modulus)
	* ----------------------------
	*	The function gets a base, an exponent and modulus and it calculate this formula
	*	base ^ exponent (mod modulus)
	*
	*	int base: the original value
	*	int exponent: the number to of times to multiply the base by itself
	*	int modulus: the number to modulus the resul of the power by
	*
	*	returns: long int.
   */
	long int ModPow(int base, int exponent, int modulus);

	IDatabase* m_database;
	long int m_publicKey;
	long int m_privateKey;
	long int m_modulus;
};