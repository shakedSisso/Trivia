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
    public partial class RoomMember : Form
    {
        private string roomName;
        private int questionCount;
        private int timePerQuestion;
        private bool isActive;
        private Newtonsoft.Json.Linq.JArray players;
        private System.Threading.Timer timer;
        private object communicatorLock;
        private bool isDisconnected;
        public RoomMember(string name)
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.Manual;
            this.Location = LocationManager.GetFormLocation();
            this.Text = name + "- Member";
            this.roomName = name;
            lblRoomName.Text = "You are connected to " + this.roomName;
            lblRoomName.Left = (this.Width - lblRoomName.Width - 20) / 2;
            this.communicatorLock = new object();
            this.isDisconnected = false;
            try
            {
                InitializeData();
                updatePlayersList();
                timer = new System.Threading.Timer(refreshData, null, 0, 3000);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        private void InitializeData()
        {
            dynamic roomState = Program.GetCommunicator().GetRoomState();
            if (roomState != null)
            {
                this.players = roomState.players;
                this.questionCount = roomState.questionCount;
                this.timePerQuestion = roomState.answerTimeOut;
                this.isActive = roomState.hasGameBegun;
                lblQuestionCount.Text = lblQuestionCount.Text + " " + this.questionCount;
                lblTimeOut.Text = lblTimeOut.Text + " " + this.timePerQuestion;
            }
        }

        private void updatePlayersList()
        {
            for (int i = this.Controls.Count - 1; i >= 0; i--)
            {
                if (this.Controls[i] is Label label && label != lblUsers && label != lblRoomName)
                {
                    this.Controls.RemoveAt(i);
                    label.Dispose();
                }
            }
            try
            {
                if (players != null)
                {
                    Label lbl;
                    for (int i = 0; i < this.players.Count; i++)
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
        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            LocationManager.SetFormLocation(this.Location);
            base.OnFormClosing(e);

            if (this.timer != null)
            {
                this.timer.Dispose();
                this.timer = null;
            }
        }

        private void refreshData(object state)
        {
            dynamic roomState;
            bool isActive = false;
            Newtonsoft.Json.Linq.JArray playerArray = new Newtonsoft.Json.Linq.JArray();
            if (this.IsHandleCreated)
            {
                lock(this.communicatorLock)
                {
                    try
                    {
                        roomState = Program.GetCommunicator().GetRoomState();
                        isActive = (bool)roomState.hasGameBegun;
                        playerArray = roomState.players;
                    }
                    catch(Exception ex)
                    {
                        Program.GetCommunicator().LeaveRoom();
                        this.isDisconnected = true;
                        this.Invoke((MethodInvoker)delegate
                        {
                            this.timer.Dispose();
                            this.timer = null;
                            MessageBox.Show("Room Closed", "The room was closed by the room admin.", MessageBoxButtons.OK, MessageBoxIcon.Information);
                            this.Dispose();
                        });
                        return;
                    }
                }
                if(isActive)
                {
                    lock(this.communicatorLock)
                    {
                        Program.GetCommunicator().StartGame();
                    }    
                    this.Invoke((MethodInvoker)delegate
                    {
                        LocationManager.SetFormLocation(this.Location);
                        Form fGame = new Game(this.roomName);
                        this.timer.Dispose();
                        this.timer = null;
                        this.Hide();
                        fGame.ShowDialog();
                        this.Dispose();
                    });
                }
                else
                {
                    this.players = playerArray;
                    this.Invoke((MethodInvoker)delegate
                    {
                        updatePlayersList();
                    });
                }

            }
        }

        private void btnLeaveGame_Click(object sender, EventArgs e)
        {
            lock(this.communicatorLock)
            {
                Program.GetCommunicator().LeaveRoom();
                this.isDisconnected = true;
            }
            this.timer.Dispose();
            this.timer = null;
            this.Dispose();
        }

        private void RoomMember_FormClosing(object sender, FormClosingEventArgs e)
        {
            if(!this.isDisconnected)
            {
                lock(this.communicatorLock)
                {
                    Program.GetCommunicator().LeaveRoom();
                }
            }
            if (this.timer != null)
            {
                this.timer.Dispose();
                this.timer = null;
            }
        }
    }
}
