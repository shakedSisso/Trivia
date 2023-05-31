using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using System.Text;
using System.Net;
using System.Windows.Forms;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;


namespace Trivia
{
    class Communicator
    {
        private Socket socket;

        private enum codes { Error, Login, Signup, GetPlayersInRoom, JoinRoom, CreateRoom, HighScore, Logout, GetRooms, Statistics, CloseRoom, StartGame, GetRoomState, LeaveRoom }
        public void Connect()
        {
            try
            {
                this.socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

                IPAddress serverIP = IPAddress.Parse("127.0.0.1");
                int serverPort = 1444;

                // Connect to the server
                this.socket.Connect(new IPEndPoint(serverIP, serverPort));
            }
            catch (Exception ex)
            {
                throw new Exception("An error occurred while trying to connect to server: " + ex.Message);
            }
        }

        public void Disconnect()
        {
            this.socket.Shutdown(SocketShutdown.Both);
            this.socket.Close();
        }

        public bool Login(string username, string password)
        {
            var jsonObject = new { username = username, password = password};
            byte[] buffer = PacketSerializer.GenerateMessage((int)codes.Login, jsonObject);
            this.socket.Send(buffer);
            dynamic response = PacketDeserializer.ProcessSocketData(this.socket);
            if(response.code == (int)codes.Error)
            {
                throw new Exception(response.message.ToString());
            }
            if(response.status == (int)codes.Login)
            {
                return true;
            }
            throw new Exception("Couldn't login");


        }

        public bool SignUp(string username, string password, string mail, string address, string phoneNumber, string birthDate)
        {
            var jsonObject = new { username = username, password = password, mail = mail, address = address, phone_number = phoneNumber, birth_date = birthDate };
            byte[] buffer = PacketSerializer.GenerateMessage((int)codes.Signup, jsonObject);
            this.socket.Send(buffer);
            dynamic response = PacketDeserializer.ProcessSocketData(this.socket);
            if (response.code == (int)codes.Error)
            {
                throw new Exception(response.message.ToString());
            }
            if (response.status == (int)codes.Signup)
            {
                return true;
            }
            throw new Exception("Couldn't signup");
        }

        public bool Logout()
        {
            var jsonObject = new { };
            byte[] buffer = PacketSerializer.GenerateMessage((int)codes.Logout, jsonObject);
            this.socket.Send(buffer);
            dynamic response = PacketDeserializer.ProcessSocketData(this.socket);
            if (response.code == (int)codes.Error)
            {
                
                throw new Exception(response.message.ToString());
            }
            if (response.status == (int)codes.Logout)
            {
                return true;
            }
            throw new Exception("Couldn't logout");
        }

        public string[] GetPlayersInRoom(int roomId)
        {
            var jsonObject = new { room_id = roomId};
            byte[] buffer = PacketSerializer.GenerateMessage((int)codes.GetPlayersInRoom, jsonObject);
            this.socket.Send(buffer);
            dynamic response = PacketDeserializer.ProcessSocketData(this.socket);
            if (response.code == (int)codes.Error)
            {
                throw new Exception(response.message.ToString());
            }
            if (response.status == (int)codes.GetPlayersInRoom)
            {
                try
                {

                    return ((JArray)response.PlayersInRoom).ToObject<string[]>();
                }
                catch (Exception ex)
                {
                    return null;
                }
            }
            throw new Exception("Error while trying to make a request");
        }
        

        public string[] GetRooms() // TODO - check how the rooms needs to be returned and if the function return type is string not raising errors
        {
            var jsonObject = new { };
            byte[] buffer = PacketSerializer.GenerateMessage((int)codes.GetRooms, jsonObject);
            this.socket.Send(buffer);
            dynamic response = PacketDeserializer.ProcessSocketData(this.socket);
            if (response.code == (int)codes.Error)
            {
                throw new Exception(response.message.ToString());
            }
            if (response.status == (int)codes.GetRooms)
            {
                try
                {

                    return ((JArray)response.Rooms).ToObject<string[]>();
                }
                catch(Exception ex)
                {
                    return null;
                }
            }
            throw new Exception("Error while trying to make a request");
        }
        


        public string[] GetHighScores()
        {
            var jsonObject = new { };
            byte[] buffer = PacketSerializer.GenerateMessage((int)codes.HighScore, jsonObject);
            this.socket.Send(buffer);
            dynamic response = PacketDeserializer.ProcessSocketData(this.socket);
            if (response.code == (int)codes.Error)
            {
                throw new Exception(response.message);
            }
            if (response.status == (int)codes.HighScore)
            {
                try
                {

                    return ((JArray)response.statistics).ToObject<string[]>();
                }
                catch (Exception ex)
                {
                    return null;
                }
            }
            throw new Exception("Error while trying to make a request");
        }


        public string[] GetStatistics()
        {
            var jsonObject = new { };
            byte[] buffer = PacketSerializer.GenerateMessage((int)codes.Statistics, jsonObject);
            this.socket.Send(buffer);
            dynamic response = PacketDeserializer.ProcessSocketData(this.socket);
            if (response.code == (int)codes.Error)
            {
                throw new Exception(response.message.ToString());
            }
            if (response.status == (int)codes.Statistics)
            {
                try
                {

                    return ((JArray)response.statistics).ToObject<string[]>();
                }
                catch(Exception ex)
                {
                    return null;
                }
            }
            throw new Exception("Error while trying to make a request");
        }

        public bool JoinRoom(int roomId)
        {
            var jsonObject = new { room_id = roomId };
            byte[] buffer = PacketSerializer.GenerateMessage((int)codes.JoinRoom, jsonObject);
            this.socket.Send(buffer);
            dynamic response = PacketDeserializer.ProcessSocketData(this.socket);
            if (response.code == (int)codes.Error)
            {
                throw new Exception(response.message.ToString());
            }
            if (response.status == (int)codes.JoinRoom)
            {
                return true;
            }
            throw new Exception("Error while trying to make a request");
        }

        public bool CreateRoom(string roomName, int maxUsers, int questionCount, int timeOut)
        {
            var jsonObject = new { room_name = roomName, max_users = maxUsers, question_count = questionCount, time_out = timeOut };
            byte[] buffer = PacketSerializer.GenerateMessage((int)codes.CreateRoom, jsonObject);
            this.socket.Send(buffer);
            dynamic response = PacketDeserializer.ProcessSocketData(this.socket);
            if (response.code == (int)codes.Error)
            {
                throw new Exception(response.message.ToString());
            }
            if (response.status == (int)codes.CreateRoom)
            {
                return true;
            }
            throw new Exception("Error while trying to make a request");
        }

        public bool CloseRoom()
        {
            var jsonObject = new { };
            byte[] buffer = PacketSerializer.GenerateMessage((int)codes.CloseRoom, jsonObject);
            this.socket.Send(buffer);
            dynamic response = PacketDeserializer.ProcessSocketData(this.socket);
            if (response.code == (int)codes.Error)
            {
                throw new Exception(response.message.ToString());
            }
            if (response.status == (int)codes.CloseRoom)
            {
                return true;
            }
            throw new Exception("Error while trying to make a request");
        }

        public bool StartGame()
        {
            var jsonObject = new { };
            byte[] buffer = PacketSerializer.GenerateMessage((int)codes.StartGame, jsonObject);
            this.socket.Send(buffer);
            dynamic response = PacketDeserializer.ProcessSocketData(this.socket);
            if (response.code == (int)codes.Error)
            {
                throw new Exception(response.message.ToString());
            }
            if (response.status == (int)codes.StartGame)
            {
                return true;
            }
            throw new Exception("Error while trying to make a request");
        }

        public dynamic GetRoomState()
        {
            var jsonObject = new { };
            byte[] buffer = PacketSerializer.GenerateMessage((int)codes.GetRoomState, jsonObject);
            this.socket.Send(buffer);
            dynamic response = PacketDeserializer.ProcessSocketData(this.socket);
            if (response.code == (int)codes.Error)
            {
                throw new Exception(response.message.ToString());
            }
            if (response.status == (int)codes.GetRoomState)
            {
                return response;
            }
            throw new Exception("Error while trying to make a request");
        }

        public bool LeaveRoom()
        {
            var jsonObject = new { };
            byte[] buffer = PacketSerializer.GenerateMessage((int)codes.LeaveRoom, jsonObject);
            this.socket.Send(buffer);
            dynamic response = PacketDeserializer.ProcessSocketData(this.socket);
            if (response.code == (int)codes.Error)
            {
                throw new Exception(response.message.ToString());
            }
            if (response.status == (int)codes.LeaveRoom)
            {
                return true;
            }
            throw new Exception("Error while trying to make a request");
        }
    }
}
