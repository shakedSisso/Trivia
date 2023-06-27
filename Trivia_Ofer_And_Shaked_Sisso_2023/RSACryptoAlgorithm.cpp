#include "RSACryptoAlgorithm.h"
#include <random>
#include <cmath>
#include <math.h>

#define ASCCII_VLUE_LOWER_THAN_A 96

RSACryptoAlgorithm::RSACryptoAlgorithm(IDatabase* database)
    : m_database(database)
{
}

Buffer RSACryptoAlgorithm::encrypt(const Buffer& message, const int& key, const int& modulus)
{
    Buffer ecrypted;
    Byte cipherText;

    for (const Byte& ch : message)
    {
        cipherText = static_cast<Byte>(ModPow(ch-ASCCII_VLUE_LOWER_THAN_A, key, modulus));
        ecrypted.push_back(cipherText);
    }

    return ecrypted;
}

Buffer RSACryptoAlgorithm::decrypt(const Buffer& message)
{
    Buffer decrypted;
    Byte plainText;
    for (const Byte& ch : message)
    {
        if (ch == '\0')
        {
            plainText = ch;
        }
        else
        {
            plainText = static_cast<Byte>(ModPow(ch + ASCCII_VLUE_LOWER_THAN_A, m_privateKey, m_modulus));
        }
        decrypted.push_back(plainText);
    }

    return decrypted;
}

void RSACryptoAlgorithm::setDatabase(IDatabase* database)
{
    this->m_database = database;
}
void RSACryptoAlgorithm::createKeys()
{
    vector<string> keys;
    keys.reserve(2);
    int p = getRandomPrime(100, 1000);
    int q = getRandomPrime(100, 1000);
    while (p == q) {
        q = getRandomPrime(2, 100);
    }

    this->m_modulus = p * q;
    long int phi = (p - 1) * (q - 1);

    findKeys(phi, p, q);
}

void RSACryptoAlgorithm::findKeys(long int phi, long int p, long int q)
{
    int i, d;
    bool flag;
    i = getRandomPrime(2, 200);
    while (i > phi)
    {
        i = getRandomPrime(2, 200);
    }
    for (;i < phi; i++)
    {
        if (phi % i == 0)
            continue;
        flag = isPrime(i);
        if (flag && i != p && i != q)
        {
            this->m_publicKey = i;
            d = findPrivateKey(phi);
            if (d > 0)
            {
                this->m_privateKey = d;
                break;
            }
        }
    }
}

long int RSACryptoAlgorithm::findPrivateKey(long int phi)
{
    long int i = 1;
    while (true)
    {
        i += phi;
        if (i % this->m_publicKey == 0)
        {
            return (i / this->m_publicKey);
        }
    }
}

std::vector<int> RSACryptoAlgorithm::getKey()
{
    std::vector<int> keys;
    keys.push_back(this->m_publicKey);
    keys.push_back(this->m_modulus);
    return keys;
}

bool RSACryptoAlgorithm::isPrime(long int number)
{
    int i;
    double j = sqrt(number);
    for (i = 2; i <= j; i++)
    {
        if (number % i == 0)
            return false;
    }
    return true;
}

int RSACryptoAlgorithm::getRandomPrime(int min, int max)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);

    int prime = dist(mt);
    while (!isPrime(prime)) 
    {
        prime = dist(mt);
    }

    return prime;
}

long int RSACryptoAlgorithm::ModPow(int base, int exponent, int modulus)
{
    long int result = base, i = 0, j = 1;
    for (i = 0; i < exponent; i++)
    {
        j *= result;
        j %= modulus;
    }
    return result;
}
