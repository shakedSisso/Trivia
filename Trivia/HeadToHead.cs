using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Trivia.Properties;

namespace Trivia
{
    public partial class HeadToHead : Form
    {
        private System.Drawing.Image resource;
        private int remainingSeconds;
        private System.Threading.Timer timer;
        private object communicatorLock;
        private bool isDisconnected;
        private Form fGame;
        public HeadToHead()
        {
            InitializeComponent();
            StartPosition = FormStartPosition.Manual;
            this.Location = LocationManager.GetFormLocation();
            this.communicatorLock = new object();
            this.isDisconnected = false;
            this.isDisconnected = false;
            try
            {
                Program.GetCommunicator().JoinHeadToHead();
                timer = new System.Threading.Timer(refreshData, null, 0, 3000);
                PickRandomLoadingImage();
                pbLoading.Image = resource;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                this.Dispose();
            }
        }

        private void PickRandomLoadingImage()
        {
            int randomNum = new Random().Next(1, 7);
            switch (randomNum)
            {
                case 1:
                    resource = Properties.Resources.loading1;
                    break;
                case 2:
                    resource = Properties.Resources.loading2;
                    break;
                case 3:
                    resource = Properties.Resources.loading3;
                    break;
                case 4:
                    resource = Properties.Resources.loading4;
                    break;
                case 5:
                    resource = Properties.Resources.loading5;
                    break;
                default:
                    resource = Properties.Resources.loading6;
                    break;
            }
        }

        private void refreshData(object? state)
        {
            dynamic roomState;
            bool doesIncludeTwoPlayers = false;
            if (this.IsHandleCreated)
            {
                lock (communicatorLock)
                {
                    try
                    {

                        roomState = Program.GetCommunicator().GetRoomState();
                        doesIncludeTwoPlayers = (bool)roomState.isActive;
                    }
                    catch (Exception ex)
                    {
                        this.Invoke((MethodInvoker)delegate
                        {
                            MessageBox.Show(ex.Message);
                            if (this.timer != null)
                            {
                                this.timer.Dispose();
                                this.timer = null;
                            }
                            this.Dispose();
                        });
                        return;
                    }
                }
                if (doesIncludeTwoPlayers)
                {
                    this.Invoke((MethodInvoker)delegate
                    {
                        lblCountDown.Visible = true;
                        lblWaiting.Visible = false;
                        pbLoading.Visible = false;
                        btnLeaveGame.Visible = false;
                        remainingSeconds = 5;
                        lblCountDown.Text = remainingSeconds.ToString();
                        if (this.timer != null)
                        {
                            this.timer.Dispose();
                            this.timer = null;
                        }
                        tmrCountDown.Start();
                    });
                }
            }
        }

        private void btnLeaveGame_Click(object sender, EventArgs e)
        {
            lock (this.communicatorLock)
            {
                Program.GetCommunicator().LeaveRoom();
                this.isDisconnected = true;
            }
            if (this.timer != null)
            {
                this.timer.Dispose();
                this.timer = null;
            }
            this.Dispose();
        }
        private void HeadToHead_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (!this.isDisconnected)
            {
                lock (this.communicatorLock)
                {
                    Program.GetCommunicator().LeaveRoom();
                }
            }
            if (this.timer != null)
            {
                this.timer.Dispose();
                this.timer = null;
            }
            LocationManager.SetFormLocation(this.Location);
        }

        private void tmrCountDown_Tick(object sender, EventArgs e)
        {
            if (this.remainingSeconds <= 0)
            {
                try
                {
                    tmrCountDown.Stop();
                    lock (this.communicatorLock)
                    {
                        Program.GetCommunicator().StartGame();
                    }
                    LocationManager.SetFormLocation(this.Location);
                    this.isDisconnected = true;
                    this.fGame = new Game("1 vs 1", 10, 15);
                    this.Hide();
                    fGame.ShowDialog();
                    this.Dispose();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            else
            {
                lblCountDown.Text = remainingSeconds.ToString();
                remainingSeconds--;
            }
        }
    }
}
