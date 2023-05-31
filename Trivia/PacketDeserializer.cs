using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using System.Text;
using System.Net;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace Trivia
{
    class PacketDeserializer
    {
        public static dynamic ProcessSocketData(Socket socket)
        {
            byte[] headerBytes = new byte[5];
            socket.Receive(headerBytes);

            // Extract code from the first byte
            byte code = headerBytes[0];
            Array.Reverse(headerBytes);

            // Extract length from the last four bytes
            int length = BitConverter.ToInt32(headerBytes, 1); 
            Array.Reverse(headerBytes);

            byte[] dataBytes = new byte[length];
            socket.Receive(dataBytes);

            string jsonString = System.Text.Encoding.UTF8.GetString(dataBytes);
            dynamic jsonObject = JsonConvert.DeserializeObject(jsonString);

            // Add the code to the JSON object
            jsonObject.code = code;

            return jsonObject;
        }

    }
}
