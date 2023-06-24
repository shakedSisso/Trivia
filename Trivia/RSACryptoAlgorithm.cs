using System;
using System.Collections.Generic;
using System.Numerics;
using System.Text;

namespace Trivia
{
    class RSACryptoAlgorithm
    {
        private static BigInteger m_modulus;
        private static BigInteger m_publicKey;
        private static BigInteger m_privateKey;

        private static Random random = new Random();

        public static void createKeys(int keyLength)
        {
            int p = getRandomPrime(2, 100);
            int q = getRandomPrime(2, 100);
            while (p == q)
            {
                q = getRandomPrime(2, 100);
            }

            m_modulus = p * q;
            int phi = (p - 1) * (q - 1);

            // Choose a public key (usually a prime number)
            m_publicKey = getRandomPrime(2, phi);

            // Ensure public key and phi are coprime
            while (GCD(m_publicKey, phi) != 1)
            {
                m_publicKey = getRandomPrime(2, phi);
            }

            // Calculate the private key using modular inverse
            m_privateKey = ModInverse(m_publicKey, phi);
        }

        public static BigInteger getPublicKey()
        {
            return m_publicKey;
        }

        public static BigInteger getModulus()
        {
            return m_modulus;
        }

        public static byte[] encrypt(byte[] plaintext, int key, int modulus)
        {
            int blockSize = getBlockSize();
            List<byte[]> blocks = splitIntoBlocks(plaintext, blockSize);
            List<byte[]> encryptedBlocks = new List<byte[]>();

            foreach (byte[] block in blocks)
            {
                //byte[] encryptedBlock = new byte[block.Length];
                //List<byte[]> encryptedBlock = new List<byte[]>();
                //int i = 0;
                foreach(byte blockByte in block)
                {

                    BigInteger plaintextValue = new BigInteger(blockByte);
                    BigInteger encryptedValue = BigInteger.ModPow(plaintextValue, key, modulus);
                    //encryptedBlock[i] = encryptedValue.ToByteArray();
                    encryptedBlocks.Add(encryptedValue.ToByteArray());
                    //i++;
                }

            }

            return mergeBlocks(encryptedBlocks);
        }

        public static byte[] decrypt(byte[] ciphertext)
        {
            int blockSize = getBlockSize();
            List<byte[]> blocks = splitIntoBlocks(ciphertext, blockSize);
            List<byte[]> decryptedBlocks = new List<byte[]>();

            foreach (byte[] block in blocks)
            {
                BigInteger encryptedValue = new BigInteger(block);
                BigInteger decryptedValue = BigInteger.ModPow(encryptedValue, m_privateKey, m_modulus);
                byte[] decryptedBlock = decryptedValue.ToByteArray();

                decryptedBlocks.Add(decryptedBlock);
            }

            return mergeBlocks(decryptedBlocks);
        }

        private static List<byte[]> splitIntoBlocks(byte[] data, int blockSize)
        {
            List<byte[]> blocks = new List<byte[]>();

            int index = 0;
            while (index < data.Length)
            {
                int remainingBytes = data.Length - index;
                int blockSizeBytes = Math.Min(blockSize, remainingBytes);
                byte[] block = new byte[blockSizeBytes];
                Array.Copy(data, index, block, 0, blockSizeBytes);
                blocks.Add(block);
                index += blockSizeBytes;
            }

            return blocks;
        }

        private static byte[] mergeBlocks(List<byte[]> blocks)
        {
            int totalLength = 0;
            foreach (byte[] block in blocks)
            {
                totalLength += block.Length;
            }

            byte[] merged = new byte[totalLength];
            int index = 0;

            foreach (byte[] block in blocks)
            {
                Array.Copy(block, 0, merged, index, block.Length);
                index += block.Length;
            }

            return merged;
        }

        private static int getBlockSize()
        {
            return 5;
        }

        private static bool isPrime(int number)
        {
            if (number <= 1)
            {
                return false;
            }

            for (int i = 2; i <= Math.Sqrt(number); i++)
            {
                if (number % i == 0)
                {
                    return false;
                }
            }

            return true;
        }

        private static int getRandomPrime(int min, int max)
        {
            int num = random.Next(min, max);
            while(!isPrime(num))
            {
                num = random.Next(min, max);
            }
            return num;
        }

        private static BigInteger GCD(BigInteger a, BigInteger b)
        {
            if (b == 0)
            {
                return a;
            }
            return GCD(b, a % b);
        }

        private static int ModInverse(BigInteger a, int m)
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

        private int ModPow(int baseNum, int exponent, int modulus)
        {
            int result = 1;
            baseNum = baseNum % modulus;

            while (exponent > 0)
            {
                if (exponent % 2 == 1)
                {
                    result = (result * baseNum) % modulus;
                }

                exponent = exponent >> 1;
                baseNum = (baseNum * baseNum) % modulus;
            }

            return result;
        }

    }
}
