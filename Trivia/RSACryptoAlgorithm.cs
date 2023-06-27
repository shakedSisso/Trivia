using System;
using System.Collections.Generic;
using System.Numerics;
using System.Reflection;
using System.Text;
using System.Windows.Forms;

namespace Trivia
{
    class RSACryptoAlgorithm
    {
        public static int m_modulus;
        public static int m_publicKey;
        private static int m_privateKey;

        private static Random random = new Random();

        private static int GetRandomPrime(int min, int max)
        {
            Random rd = new Random();
            int prime = rd.Next(min, max + 1);
            while (!IsPrime(prime))
            {
                prime = rd.Next(min, max + 1);
            }

            return prime;
        }

        public static void CreateKeys()
        {
            List<int> keys = new List<int>(2);
            int p = GetRandomPrime(100, 1000);
            int q = GetRandomPrime(100, 1000);
            while (p == q)
            {
                q = GetRandomPrime(2, 100);
            }
            Console.WriteLine("p: " + p + " q: " + q);

            m_modulus = p * q;
            long phi = (p - 1) * (q - 1);

            FindKeys(phi, p, q);
        }
        private static void FindKeys(long phi, long p, long q)
        {
            int i, d;
            bool flag;
            i = GetRandomPrime(2, 200);
            while (i > phi)
            {
                i = GetRandomPrime(2, 200);
            }
            for (; i < phi; i++)
            {
                if (phi % i == 0)
                    continue;
                flag = IsPrime(i);
                if (flag && i != p && i != q)
                {
                    m_publicKey = i;
                    d = FindPrivateKey(phi);
                    if (d > 0)
                    {
                        m_privateKey = d;
                        break;
                    }
                }
            }
        }
        private static int FindPrivateKey(long phi)
        {
            long i = 1;
            while (true)
            {
                i += phi;
                if (i % m_publicKey == 0)
                {
                    return ((int)i / m_publicKey);
                }
            }
        }

        public static long getPublicKey()
        {
            return m_publicKey;
        }

        public static long getModulus()
        {
            return m_modulus;
        }

        public static byte[] Encrypt(byte[] plaintext, int key, int modulus)
        {
            List<byte> ecrypted = new List<byte>();

            foreach (byte ch in plaintext)
            {
                byte plainText = (byte)(ModPow((ch - 96), m_publicKey, m_modulus));
                ecrypted.Add(plainText);
            }

            return ecrypted.ToArray();
        }

        public static byte[] Decrypt(byte[] ciphertext)
        {
            List<byte> decrypted = new List<byte>();

            foreach (byte ch in ciphertext)
            {
                byte plainText = (byte)(ModPow(ch + 96, m_privateKey, m_modulus));
                decrypted.Add(plainText);
            }

            return decrypted.ToArray();
        }

        private static bool IsPrime(int number)
        {
            int i;
            double j = Math.Sqrt(number);
            for (i = 2; i <= j; i++)
            {
                if (number % i == 0)
                    return false;
            }
            return true;
        }
        private static long ModPow(int baseValue, int exponent, int modulus)
        {
            long result = baseValue;
            long j = 1;
            for (int i = 0; i < exponent; i++)
            {
                j *= result;
                j %= modulus;
            }
            return result;
        }

    }
}
