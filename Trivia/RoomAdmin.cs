using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Trivia
{
    public partial class RoomAdmin : Form
    {
        private Thread updateThread;
        private bool threadFlag;
        private string roomName;
        private int maxPlayers;
        private int questionCount;
        private int timePerQuestion;
        public RoomAdmin(string name)
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.CenterScreen;
            this.roomName = name;
            lblRoomName.Text = "You are connected to " + this.roomName;
            lblRoomName.Left = (this.Width - lblRoomName.Width - 20) / 2;
            try
            {
                updatePlayersList(); 
                this.updateThread = new Thread(updatePlayersList);
                this.threadFlag = true;
                this.updateThread.Start();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void updatePlayersList()
        {
            Program.GetCommunicator().GetRoomState();
            //update list of players connected to the room
        }

        private void joinThread()
        {
            this.threadFlag = false;
            this.updateThread?.Join();
        }

        private void btnCloseGame_Click(object sender, EventArgs e)
        {
            Program.GetCommunicator().CloseRoom();
            joinThread();
            this.Dispose();
        }

        private void btnStartGame_Click(object sender, EventArgs e)
        {
            Program.GetCommunicator().StartGame();
            Form fGame = new Game(this.roomName);
            this.Hide();
            joinThread();
            fGame.ShowDialog();
            this.Dispose();
        }
    }
}
