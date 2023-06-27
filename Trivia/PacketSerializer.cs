using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.Json;

namespace Trivia
{
    class PacketSerializer
    {
        private const int BITS_IN_BYTE = 8;
        private const int BYTE_MASK = 0xFF;

        public static void InsertIntToBuffer(List<byte> buffer, int num, int bytes)
        {
            for (int i = bytes - 1; i >= 0; i--)
            {
                byte byteValue = (byte)((num >> (BITS_IN_BYTE * i)) & BYTE_MASK);
                buffer.Add(byteValue);
            }
        }

        public static byte[] GenerateMessage(int code, object jsonObject, int key, int modulus)
        {
            List<byte> buffer = new List<byte>();

            // Insert code as ASCII value
            InsertIntToBuffer(buffer, code, 1);
            buffer = RSACryptoAlgorithm.Encrypt(buffer.ToArray(), key, modulus).ToList<byte>();

            string jsonString = System.Text.Json.JsonSerializer.Serialize(jsonObject);
            byte[] jsonStringBytes = System.Text.Encoding.UTF8.GetBytes(jsonString);
            byte[] encryptedJson = RSACryptoAlgorithm.Encrypt(jsonStringBytes, key, modulus);

            // Insert JSON string length as ASCII value
            byte[] encryptedLength = { (byte)encryptedJson.Length };
            byte[] length = RSACryptoAlgorithm.Encrypt(encryptedLength, key, modulus);

            int lengthHeader = length.Length;
            while (lengthHeader < 4)
            {
                buffer.Add((byte) 0);
                lengthHeader++;
            }
            buffer.AddRange(length);

            // Insert JSON string
            buffer.AddRange(encryptedJson);

            return buffer.ToArray();
        }


    }
}
