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
        private RoomData[] rooms;
        private int roomId;
        private System.Threading.Timer timer;
        private object communicatorLock;

        public ConnectToRoom(Point startLocation)
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.Manual;
            this.Location = startLocation;
            btnRefresh.Visible = true;
            btnJoinRoom.Visible = true;
            this.communicatorLock = new object();
            try
            {
                this.roomId = -999;
                this.rooms = Program.GetCommunicator().GetRooms();
                updateRoomsList();
                btnJoinRoom.Enabled = false;
                timer = new System.Threading.Timer(refreshData, null, 0, 3000);
            }
            catch (Exception ex)
            {
                throw new Exception(ex.Message);
            }
        }

        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            base.OnFormClosing(e);

            if(this.timer != null)
            {
                this.timer.Dispose();
                this.timer = null;
            }
        }

        private void refreshData(object state)
        {
            if(this.IsHandleCreated)
            {
                lock(this.communicatorLock)
                {
                    this.rooms = Program.GetCommunicator().GetRooms();
                }
                this.Invoke((MethodInvoker)delegate {
                    updateRoomsList();
                });
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
                        btn.Left = gbRooms.Left - 55;
                        btn.Top = gbRooms.Top + 10 + 30 * i;
                        btn.Width = gbRooms.Width + 10;
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
            string[] players;
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
                lock(this.communicatorLock)
                {
                    players = Program.GetCommunicator().GetPlayersInRoom(this.roomId);
                }
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

        private void btnBack_Click(object sender, EventArgs e)
        {
            this.timer.Dispose();
            this.timer = null;
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
            lock (this.communicatorLock)
            {
                this.rooms = Program.GetCommunicator().GetRooms();
            }
            updateRoomsList();
            btnJoinRoom.Enabled = false;
        }

        private void btnJoinRoom_Click(object sender, EventArgs e)
        {
            lock(this.communicatorLock)
            {
                if (this.roomId != -999 && Program.GetCommunicator().JoinRoom(this.roomId))
                {
                    string roomName = string.Empty;
                    for (int i = 0; i < this.rooms.Length; i++)
                    {
                        if (this.rooms[i].id == this.roomId)
                            roomName = this.rooms[i].name;
                    }
                    Form fRoomMember = new RoomMember(this.Location, roomName);
                    this.timer.Dispose();
                    this.timer = null;
                    this.Hide();
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
}
