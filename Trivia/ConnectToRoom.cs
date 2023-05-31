using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;

namespace Trivia
{
    public partial class ConnectToRoom : Form
    {

        private Thread updateThread;
        private bool threadFlag;
        private string[] rooms;
        public ConnectToRoom()
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.CenterScreen;
            try
            {
                this.rooms = Program.GetCommunicator().GetRooms();
                updateRoomsList();
                this.updateThread = new Thread(getUpdatedRoomList);
                this.threadFlag = true;
                this.updateThread.Start();
            }
            catch (Exception ex)
            {
                throw new Exception(ex.Message);
            }
        }

        private void updateRoomsList()
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.threadFlag = false;
            this.updateThread?.Join();
            this.Dispose();
        }

        private void getUpdatedRoomList()
        {
            while(this.threadFlag)
            {
                this.rooms = Program.GetCommunicator().GetRooms();
                updateRoomsList();
                Thread.Sleep(3000);
            }
        }

    }
}
