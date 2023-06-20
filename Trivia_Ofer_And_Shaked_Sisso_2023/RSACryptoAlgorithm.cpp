#include "RSACryptoAlgorithm.h"
#include <random>
#include <cmath>

#define BLOCK_SIZE 5

Buffer RSACryptoAlgorithm::encrypt(const Buffer& message, const int& key, const int& modulus)
{
    Buffer ciphertext;
    Buffer block;
    int blockSize = GetBlockSize();

    for (Byte c : message) 
    {
        block.push_back(c);

        if (block.size() == blockSize) 
        {
            Buffer encryptedBlock = EncryptBlock(block, key, modulus);
            ciphertext.insert(ciphertext.end(), encryptedBlock.begin(), encryptedBlock.end());
            block.clear();
        }
    }

    if (!block.empty()) 
    {
        Buffer encryptedBlock = EncryptBlock(block, key, modulus);
        ciphertext.insert(ciphertext.end(), encryptedBlock.begin(), encryptedBlock.end());
    }

    return ciphertext;
}

Buffer RSACryptoAlgorithm::decrypt(const Buffer& message)
{
    Buffer decryptedText;
    Buffer block;
    int blockSize = GetBlockSize();

    for (Byte c : message) 
    {
        block.push_back(c);

        if (block.size() == blockSize) 
        {
            Buffer decryptedBlock = DecryptBlock(block);
            decryptedText.insert(decryptedText.end(), decryptedBlock.begin(), decryptedBlock.end());
            block.clear();
        }
    }

    if (!block.empty()) {
        Buffer decryptedBlock = DecryptBlock(block);
        decryptedText.insert(decryptedText.end(), decryptedBlock.begin(), decryptedBlock.end());
    }

    return decryptedText;
}

Buffer RSACryptoAlgorithm::EncryptBlock(const Buffer& block, const int& key, const int& modulus)
{
    Buffer encryptedBlock;

    int blockSize = block.size();
    std::vector<int> plaintextValues(blockSize);

    for (int i = 0; i < blockSize; ++i) {
        plaintextValues[i] = static_cast<int>(block[i]);
    }

    // Perform the encryption on the block of plaintext values
    // using the RSA algorithm

    for (int plaintextValue : plaintextValues) {
        int encryptedValue = ModPow(plaintextValue, key, modulus);
        encryptedBlock.push_back(static_cast<unsigned char>(encryptedValue));
    }

    return encryptedBlock;
}

Buffer RSACryptoAlgorithm::DecryptBlock(const Buffer& block)
{
    Buffer decryptedBlock;

    int blockSize = block.size();
    std::vector<int> encryptedValues(blockSize);

    for (int i = 0; i < blockSize; ++i) {
        encryptedValues[i] = static_cast<int>(block[i]);
    }

    // Perform the decryption on the block of encrypted values
    // using the RSA algorithm

    for (int encryptedValue : encryptedValues) {
        int decryptedValue = ModPow(encryptedValue, this->m_privateKey, this->m_modulus);
        decryptedBlock.push_back(static_cast<unsigned char>(decryptedValue));
    }

    return decryptedBlock;
}

int RSACryptoAlgorithm::GetBlockSize()
{
    return BLOCK_SIZE;
}

void RSACryptoAlgorithm::createKeys(int keyLength)
{
    //vector<string> keys;
    //keys.reserve(2);
    int p = getRandomPrime(2, 100);
    int q = getRandomPrime(2, 100);
    while (p == q) {
        q = getRandomPrime(2, 100);
    }

    this->m_modulus = p * q;
    int phi = (p - 1) * (q - 1);

    // Choose a public key (usually a prime number)
    this->m_publicKey = getRandomPrime(2, phi);

    // Ensure public key and phi are coprime
    while (GCD(this->m_publicKey, phi) != 1) 
    {
        this->m_publicKey = getRandomPrime(2, phi);
    }

    // Calculate the private key using modular inverse
    this->m_privateKey = ModInverse(this->m_publicKey, phi);
}

bool RSACryptoAlgorithm::isPrime(int number)
{
    if (number <= 1)
    {
        return false;
    }

    for (int i = 2; i <= std::sqrt(number); i++) 
    {
        if (number % i == 0)
        {
            return false;
        }
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

int RSACryptoAlgorithm::GCD(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    return GCD(b, a % b);
}

int RSACryptoAlgorithm::ModInverse(int a, int m)
{
    a = a % m;

    for (int x = 1; x < m; ++x) 
    {
        if ((a * x) % m == 1)
        {
            return x;
        }
    }

    return -1; // Modular inverse does not exist
}

int RSACryptoAlgorithm::ModPow(int base, int exponent, int modulus)
{
    int result = 1;
    base = base % modulus;

    while (exponent > 0) 
    {
        if (exponent % 2 == 1) 
        {
            result = (result * base) % modulus;
        }

        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }

    return result;
}
