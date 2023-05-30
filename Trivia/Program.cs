using System.Net.Sockets;
using System.Text;
using System.Net;

namespace Trivia
{
    internal static class Program
    {
        private static Communicator communicator;

        public static Communicator GetCommunicator()
        {
            return communicator;
        }

        /// <summary>
        ///  The main entry point for the application.
        /// </summary>
        [STAThread]
        
        static void Main()
        {
            // To customize application configuration such as set high DPI settings or default font,
            // see https://aka.ms/applicationconfiguration.
            communicator = new Communicator();
            communicator.Connect();
            ApplicationConfiguration.Initialize();
            Application.Run(new Trivia());
        }
    }
}