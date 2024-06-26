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
using System.Text.Json;
using Newtonsoft.Json.Linq;
using System.Numerics;


namespace Trivia
{
    class Communicator
    {
        private Socket socket;
        private int serverPublicKey;
        private int serverModulus;
        private const string DISCONNECTION_MESSAGE = "An existing connection was forcibly closed by the remote host.";
        private const string ABORT_MESSAGE = "An established connection was aborted by the software in your host machine.";
        private const string RUNTIME_MESSAGE = "Cannot perform runtime binding on a null reference";
        private string[] errors = { DISCONNECTION_MESSAGE, ABORT_MESSAGE, RUNTIME_MESSAGE };

        public bool aborted;
        public enum codes { Error, Login, Signup, GetPlayersInRoom, JoinRoom, CreateRoom, HighScore, Logout, GetRooms, Statistics, CloseRoom, StartGame, GetRoomState, LeaveRoom, LeaveGame, GetQuestion, GetQuestionFailed, SubmitAnswer, GetGameResult, GetGameResultFailed, AddQuestion, HeadToHead };
        public void Connect()
        {
            try
            {
                aborted = false;
                this.socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

                IPAddress serverIP = IPAddress.Parse("127.0.0.1");
                int serverPort = 1444;

                // Connect to the server
                this.socket.Connect(new IPEndPoint(serverIP, serverPort));
                RSACryptoAlgorithm.CreateKeys();
                sendKeys();
                getServerKeys();
            }
            catch (Exception ex)
            {
                throw new Exception("An error occurred while trying to connect to server: " + ex.Message);
            }
        }

        public void getServerKeys()
        {
            byte[] serverPublicKeyHeader = new byte[4];
            byte[] serverModulusHeader = new byte[4];
            int serverKeyLength = 0;
            int serverModulusLength = 0;

            socket.Receive(serverPublicKeyHeader);
            Array.Reverse(serverPublicKeyHeader);
            serverKeyLength = BitConverter.ToInt32(serverPublicKeyHeader);
            byte[] serverPublicKeyMessage = new byte[serverKeyLength];
            socket.Receive(serverPublicKeyMessage);
            serverPublicKey = int.Parse(Encoding.ASCII.GetString(serverPublicKeyMessage));

            socket.Receive(serverModulusHeader);
            Array.Reverse(serverModulusHeader);
            serverModulusLength = BitConverter.ToInt32(serverModulusHeader);
            byte[] serverModulusMessage = new byte[serverModulusLength];
            socket.Receive(serverModulusMessage);
            serverModulus = int.Parse(Encoding.ASCII.GetString(serverModulusMessage));
        }

        public void sendKeys()
        {
            List<byte> keyMessageBuffer = new List<byte>();
            List<byte> modulusMessageBuffer = new List<byte>();
            long publicKey = RSACryptoAlgorithm.getPublicKey();
            long modulus = RSACryptoAlgorithm.getModulus();
            int publicKeyLen = publicKey.ToString().Length;
            int modulusLen = modulus.ToString().Length;

            PacketSerializer.InsertIntToBuffer(keyMessageBuffer, ((int)publicKeyLen), 4);
            keyMessageBuffer.AddRange(Encoding.ASCII.GetBytes(publicKey.ToString()));
            this.socket.Send(keyMessageBuffer.ToArray());

            PacketSerializer.InsertIntToBuffer(modulusMessageBuffer, ((int)modulusLen), 4);
            modulusMessageBuffer.AddRange(Encoding.ASCII.GetBytes(modulus.ToString()));
            this.socket.Send(modulusMessageBuffer.ToArray());

        }

        public void Disconnect()
        {
            this.socket.Shutdown(SocketShutdown.Both);
            this.socket.Close();
        }

        private dynamic GetResponse(object jsonObject, int code)
        {
            dynamic response = null;
            try
            {
                byte[] buffer = PacketSerializer.GenerateMessage(code, jsonObject, serverPublicKey ,serverModulus);
                this.socket.Send(buffer);
                response = PacketDeserializer.ProcessSocketData(this.socket);
            }
            catch (Exception e)
            {
                if (Array.Exists(errors, msg => msg == e.Message))
                {
                    aborted = true;
                    MessageBox.Show(e.Message, "Host disconnected", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    Application.Exit();
                    return null;
                }
                else
                {
                    throw new Exception(e.Message);
                }
            }
            return response;
        }

        public bool Login(string username, string password)
        {
            var jsonObject = new { username = username, password = password };
            dynamic response = GetResponse(jsonObject, (int)codes.Login);
            if (response.code == (int)codes.Error)
            {
                throw new Exception(response.message.ToString());
            }
            if (response.status == (int)codes.Login)
            {
                return true;
            }
            throw new Exception("Couldn't login");


        }

        public bool SignUp(string username, string password, string mail, string address, string phoneNumber, string birthDate)
        {
            var jsonObject = new { username = username, password = password, mail = mail, address = address, phone_number = phoneNumber, birth_date = birthDate };
            dynamic response = GetResponse(jsonObject, (int)codes.Signup);
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
            dynamic response = GetResponse(jsonObject, (int)codes.Logout);
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
            var jsonObject = new { room_id = roomId };
            dynamic response = GetResponse(jsonObject, (int)codes.GetPlayersInRoom);
            if (response.code == (int)codes.Error)
            {
                throw new Exception(response.message.ToString());
            }
            if (response.code == (int)codes.GetPlayersInRoom)
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
        public RoomData[] GetRooms()
        {
            RoomData[] rooms = null;
            var jsonObject = new { };
            dynamic response = GetResponse(jsonObject, (int)codes.GetRooms);
            if (response.code == (int)codes.Error)
            {
                throw new Exception(response.message.ToString());
            }
            if (response.status == (int)codes.GetRooms)
            {
                if (response.Rooms != null)
                {
                    rooms = JsonConvert.DeserializeObject<RoomData[]>((response.Rooms).ToString());
                }
                return rooms;
            }
            throw new Exception("Error while trying to make a request");
        }



        public string[] GetHighScores()
        {
            var jsonObject = new { };
            dynamic response = GetResponse(jsonObject, (int)codes.HighScore);
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
            dynamic response = GetResponse(jsonObject, (int)codes.Statistics);
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
                catch (Exception ex)
                {
                    return null;
                }
            }
            throw new Exception("Error while trying to make a request");
        }

        public bool JoinRoom(int roomId)
        {
            var jsonObject = new { room_id = roomId };
            dynamic response = GetResponse(jsonObject, (int)codes.JoinRoom);
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

        public bool CreateRoom(string roomName, int maxUsers, int questionCount, int timeOut, bool includeUserQuestion)
        {
            var jsonObject = new { room_name = roomName, max_users = maxUsers, question_count = questionCount, time_out = timeOut, include_user_questions = includeUserQuestion };
            dynamic response = GetResponse(jsonObject, (int)codes.CreateRoom);
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
            dynamic response = GetResponse(jsonObject, (int)codes.CloseRoom);
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
            dynamic response = GetResponse(jsonObject, (int)codes.StartGame);
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
            dynamic response = GetResponse(jsonObject, (int)codes.GetRoomState);
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
            dynamic response = GetResponse(jsonObject, (int)codes.LeaveRoom);
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

        public dynamic GetQuestion()
        {
            var jsonObject = new { };
            dynamic response = GetResponse(jsonObject, (int)codes.GetQuestion);
            if (response.code == (int)codes.Error)
            {
                throw new Exception(response.message.ToString());
            }
            if (response.status == (int)codes.GetQuestion || response.status == (int)codes.GetQuestionFailed)
            {
                return response;
            }
            throw new Exception("Error while trying to make a request");
        }

        public int SubmitAnswer(int id, int answeringTime)
        {
            var jsonObject = new { answer_id = id, answer_time = answeringTime };
            dynamic response = GetResponse(jsonObject, (int)codes.SubmitAnswer);
            if (response.code == (int)codes.Error)
            {
                throw new Exception(response.message.ToString());
            }
            if (response.status == (int)codes.SubmitAnswer)
            {
                return response.correctAnswerId;
            }
            throw new Exception("Error while trying to make a request");
        }

        public void LeaveGame()
        {
            var jsonObject = new { };
            dynamic response = GetResponse(jsonObject, (int)codes.LeaveGame);
            if (response.code == (int)codes.Error)
            {
                throw new Exception(response.message.ToString());
            }
            if (response.code == (int)codes.LeaveGame)
            {
                return;
            }
            throw new Exception("Error while trying to make a request");
        }

        public dynamic GetGameResults()
        {
            var jsonObject = new { };
            dynamic response = GetResponse(jsonObject, (int)codes.GetGameResult);
            if (response.code == (int)codes.Error)
            {
                throw new Exception(response.message.ToString());
            }
            if (response.status == (int)codes.GetGameResult)
            {
                return response;
            }
            if (response.status == (int)codes.GetGameResultFailed)
            {
                return null;
            }
            throw new Exception("Error while trying to make a request");
        }

        internal void AddQuestion(string author, string question, string correctAnswer, string answer2, string answer3, string answer4)
        {

            var jsonObject = new { author = author, question = question, correctAns = correctAnswer, ans2 = answer2, ans3 = answer3, ans4 = answer4 };
            dynamic response = GetResponse(jsonObject, (int)codes.AddQuestion);
            if (response.code == (int)codes.Error)
            {
                throw new Exception(response.message.ToString());
            }
            if (response.status == (int)codes.AddQuestion)
            {
                return;
            }
            throw new Exception("Error while trying to make a request");
        }
        internal void JoinHeadToHead()
        {
            var jsonObject = new { };
            dynamic response = GetResponse(jsonObject, (int)codes.HeadToHead);
            if (response.code == (int)codes.Error)
            {
                throw new Exception(response.message.ToString());
            }
            if (response.status == (int)codes.HeadToHead)
            {
                return;
            }

            throw new Exception("Error while trying to make a request");
        }
    }
}
