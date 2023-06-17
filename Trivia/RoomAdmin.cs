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
using System.Timers;
using System.Security.Cryptography.X509Certificates;

namespace Trivia
{
    public partial class RoomAdmin : Form
    {
        private bool threadFlag;
        private string roomName;
        private int maxPlayers;
        private int questionCount;
        private int timePerQuestion;
        private Newtonsoft.Json.Linq.JArray players;
        private bool isActive;
        private System.Threading.Timer timer;
        private object communicatorLock;
        private bool isClosed;
        private bool isLocked;
        public RoomAdmin(string name, int maxUsers)
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.Manual;
            this.Location = LocationManager.GetFormLocation();
            this.Text = name + "- Admin";
            this.roomName = name;
            this.maxPlayers = maxUsers;
            lblRoomName.Text = "You are connected to " + this.roomName;
            lblRoomName.Left = (this.Width - lblRoomName.Width - 20) / 2;
            this.communicatorLock = new object();
            this.isClosed = false;
            this.isLocked = false;
            try
            {
                InitializeData();
                updatePlayersList();
                timer = new System.Threading.Timer(refreshData, null, 0, 3000);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                this.Dispose();
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
            try
            {
                if (this.IsHandleCreated && !isClosed)
                {
                    lock (communicatorLock)
                    {
                        this.isLocked = true;
                        this.players = Program.GetCommunicator().GetRoomState().players;
                        this.isLocked = false;

                        this.Invoke((MethodInvoker)delegate
                        {
                            updatePlayersList();
                        });
                    }
                }
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void InitializeData()
        {
            dynamic roomState;
            lock(communicatorLock)
            {
                this.isLocked = true;
                roomState = Program.GetCommunicator().GetRoomState();
                this.isLocked = false;
            }
            if (roomState != null)
            {
                this.players = roomState.players;
                this.questionCount = roomState.questionCount;
                this.timePerQuestion = roomState.answerTimeOut;
                this.isActive = roomState.hasGameBegun;
                lblMaxNumber.Text = lblMaxNumber.Text + " " + this.maxPlayers;
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


        private void btnCloseGame_Click(object sender, EventArgs e)
        {
            lock(communicatorLock)
            {
                try
                {
                    this.isLocked = false;
                    Program.GetCommunicator().CloseRoom();
                    this.isLocked = true;
                    this.isClosed = true;
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
            this.timer.Dispose();
            this.timer = null;
            this.Dispose();
        }

        private void btnStartGame_Click(object sender, EventArgs e)
        {
            try
            {
                LocationManager.SetFormLocation(this.Location);
                Form fGame = new Form(); //putting new Form() in the value to avoid error
                lock (communicatorLock)
                {
                    this.isLocked = true;
                    Program.GetCommunicator().StartGame();
                    this.isClosed = true;
                    fGame = new Game(this.roomName, this.timePerQuestion, this.questionCount);
                    if (this.timer != null)
                    {
                        this.timer.Dispose();
                        this.timer = null;
                    }
                    this.isLocked = false;
                }
                this.Hide();
                fGame.ShowDialog();
                this.Dispose();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                this.isClosed = false;
                this.Dispose();
            }

        }

        private void RoomAdmin_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (Program.GetCommunicator().aborted)
            {
                Application.Exit();
                return;
            }
            if (!this.isClosed)
            {
                lock(communicatorLock)
                {
                    try
                    {
                        this.isLocked= true;
                        Program.GetCommunicator().CloseRoom();
                        this.isLocked = false;
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show(ex.Message);
                    }
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
