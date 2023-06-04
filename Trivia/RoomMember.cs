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
        private Newtonsoft.Json.Linq.JArray players;
        private System.Threading.Timer timer;
        public RoomMember(string name)
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.CenterScreen;
            this.roomName = name;
            lblRoomName.Text = "You are connected to " + this.roomName;
            lblRoomName.Left = (this.Width - lblRoomName.Width - 20) / 2;
            try
            {
                this.players = Program.GetCommunicator().GetRoomState().players;
                updatePlayersList();
                timer = new System.Threading.Timer(refreshData, null, 0, 3000);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
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
            base.OnFormClosing(e);

            if (this.timer != null)
            {
                this.timer.Dispose();
                this.timer = null;
            }
        }

        private void refreshData(object state)
        {
            if (this.IsHandleCreated)
            {
                dynamic roomState = Program.GetCommunicator().GetRoomState();
                if((bool)roomState.hasGameBegun)
                {
                    Program.GetCommunicator().StartGame();
                    this.Invoke((MethodInvoker)delegate
                    { 
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
                    this.players = roomState.players;
                    this.Invoke((MethodInvoker)delegate
                    {
                        updatePlayersList();
                    });
                }
                
            }
        }

        private void btnLeaveGame_Click(object sender, EventArgs e)
        {
            Program.GetCommunicator().LeaveRoom();
            this.timer.Dispose();
            this.timer = null;
            this.Dispose();
        }
    }
}
