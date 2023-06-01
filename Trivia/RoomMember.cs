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
    public partial class RoomMember : Form
    {
        private Thread updateThread;
        private bool threadFlag;
        private string roomName;
        private int questionCount;
        private int timePerQuestion;
        public RoomMember(string name)
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

        private void joinThread()
        {
            this.threadFlag = false;
            this.updateThread?.Join();
        }

        private void updatePlayersList()
        {
            Program.GetCommunicator().GetRoomState();
            //update list of players connected to the room
        }

        private void btnLeaveGame_Click(object sender, EventArgs e)
        {
            Program.GetCommunicator().LeaveRoom();
            joinThread();
            this.Dispose();
        }
    }
}
