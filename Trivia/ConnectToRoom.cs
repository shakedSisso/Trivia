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
        private RoomData[] rooms;
        private int roomId;
        public ConnectToRoom()
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.CenterScreen;
            btnRefresh.Visible = true;
            btnJoinRoom.Visible = true;
            try
            {
                this.roomId = -999;
                this.rooms = Program.GetCommunicator().GetRooms();
                updateRoomsList();
                btnJoinRoom.Enabled = false;
                this.updateThread = new Thread(updateRoomsList);
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
            foreach (Control control in gbRooms.Controls)
            {
                if (control is Button)
                {
                    gbRooms.Controls.Remove(control);
                    control.Dispose();

                }
            }
            if (rooms == null)
            {
                lblNoRooms.Visible = true;
            }
            else
            {
                lblNoRooms.Visible = false;
                Button btn;
                for (int i = 0; i < this.rooms.Length; i++)
                {
                    if (!this.rooms[i].isActive)
                    {
                        btn = new Button();
                        btn.Left = gbRooms.Left - 50;
                        btn.Top = gbRooms.Top + 10 + 30 * i;
                        btn.Width = gbRooms.Width;
                        btn.Height = 30;
                        btn.Text = this.rooms[i].name;
                        btn.Tag = this.rooms[i].id;
                        btn.Font = btnBack.Font;
                        btn.ForeColor = Color.DarkSlateGray;
                        gbRooms.Controls.Add(btn);
                        btn.Click += Btn_Click;
                    }
                }
            }
        }

        private void Btn_Click(object? sender, EventArgs e)
        {
            lblUsers.Visible = true;
            pbUsers.Visible = true;
            btnJoinRoom.Enabled = true;
            for (int i = this.Controls.Count - 1; i >= 0; i--)
            {
                if (this.Controls[i] is Label label && label != lblUsers)
                {
                    this.Controls.RemoveAt(i);
                    label.Dispose();
                }
            }
            try
            {
                Button button = (Button)sender;
                this.roomId = (int)button.Tag;
                string[] players = Program.GetCommunicator().GetPlayersInRoom(this.roomId);
                if (players != null)
                {
                    Label lbl;
                    for (int i = 0; i < players.Length; i++)
                    {
                        lbl = new Label();
                        lbl.Left = lblUsers.Left;
                        lbl.Top = lblUsers.Bottom + 30 * i;
                        lbl.Text = players[i].ToString();
                        lbl.Font = new Font("Maiandra GD", 12, FontStyle.Bold);
                        lbl.ForeColor = Color.DarkSlateGray;
                        lbl.BackColor = Color.MintCream;
                        lbl.BringToFront();
                        this.Controls.Add(lbl);
                    }
                }
                pbUsers.SendToBack();
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

        private void btnBack_Click(object sender, EventArgs e)
        {
            joinThread();
            this.Dispose();
        }

        private void btnRefresh_Click(object sender, EventArgs e)
        {
            for (int i = this.Controls.Count - 1; i >= 0; i--)
            {
                if (this.Controls[i] is Label label && label != lblUsers)
                {
                    this.Controls.RemoveAt(i);
                    label.Dispose();
                }
            }
            lblUsers.Visible = false;
            pbUsers.Visible = false;
            this.roomId = -999;
            updateRoomsList();
            btnJoinRoom.Enabled = false;
        }

        private void btnJoinRoom_Click(object sender, EventArgs e)
        {
            if (this.roomId != -999 && Program.GetCommunicator().JoinRoom(this.roomId))
            {
                string roomName = string.Empty;
                for (int i = 0; i < this.rooms.Length; i++)
                {
                    if (this.rooms[i].id == this.roomId)
                        roomName = this.rooms[i].name;
                }
                Form fRoomMember = new RoomMember(roomName);
                this.Hide();
                joinThread();
                fRoomMember.ShowDialog();
                this.Dispose();
            }
            else
            {
                throw new Exception("Couldn't connect to the room");
            }
        }
    }
}
