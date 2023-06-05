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

        public static byte[] GenerateMessage(int code, object jsonObject)
        {
            List<byte> buffer = new List<byte>();

            // Insert code as ASCII value
            InsertIntToBuffer(buffer, code, 1);

            string jsonString = System.Text.Json.JsonSerializer.Serialize(jsonObject);

            // Insert JSON string length as ASCII value
            InsertIntToBuffer(buffer, jsonString.Length, 4);

            // Insert JSON string
            byte[] jsonStringBytes = System.Text.Encoding.UTF8.GetBytes(jsonString);
            buffer.AddRange(jsonStringBytes);

            return buffer.ToArray();
        }


    }
}
