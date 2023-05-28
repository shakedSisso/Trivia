using System.Net.Sockets;
using System.Text;
using System.Net;

namespace Trivia
{
    internal static class Program
    {
        /// <summary>
        ///  The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            // To customize application configuration such as set high DPI settings or default font,
            // see https://aka.ms/applicationconfiguration.
            ApplicationConfiguration.Initialize();
            Application.Run(new Trivia());
        }

        public static void communicator()
        {
            try
            {
                Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

                IPAddress serverIP = IPAddress.Parse("127.0.0.1");
                int serverPort = 1444; 

                // Connect to the server
                socket.Connect(new IPEndPoint(serverIP, serverPort));

                //Console.WriteLine("Connected to the server.");

                //string message = "Hello, server!";
                //byte[] buffer = Encoding.ASCII.GetBytes(message);
                //socket.Send(buffer);

                //// Receive data from the server
                //byte[] receiveBuffer = new byte[1024];
                //int bytesRead = socket.Receive(receiveBuffer);
                //string receivedMessage = Encoding.ASCII.GetString(receiveBuffer, 0, bytesRead);
                //Console.WriteLine("Received from server: " + receivedMessage);

                // Close the socket
                socket.Shutdown(SocketShutdown.Both);
                socket.Close();
            }
            catch (Exception ex)
            {
                Console.WriteLine("An error occurred: " + ex.Message);
            }
        }
    }
}