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
    public partial class Menu : Form
    {
        private string username;
        public Menu(string username)
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.Manual;
            this.Location = LocationManager.GetFormLocation();
            lblUsername.Text = "Hello " + username + "!";
            this.username = username;
            lblUsername.Left = (this.Width - lblUsername.Width - 20) / 2;
            this.FormClosing += Menu_FormClosing;
        }

        private void Menu_FormClosing(object? sender, FormClosingEventArgs e)
        {
            try
            {
                if (Program.GetCommunicator().aborted)
                {
                    Application.Exit();
                    return;
                }
                Program.GetCommunicator().Logout();
                Program.GetCommunicator().Disconnect();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                return;
            }
        }

        private void btnQuit_Click(object sender, EventArgs e)
        {
            try
            {
                DialogResult result = MessageBox.Show("Are you sure you want to log out?", "Confirmation", MessageBoxButtons.YesNo, MessageBoxIcon.Question);

                if (result == DialogResult.Yes)
                {
                    this.Hide();
                    MessageBox.Show("Goodbye!");
                    Application.Exit();
                }
                else if (result == DialogResult.No)
                {
                    return;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                return;
            }
        }

        private void btnBestScores_Click(object sender, EventArgs e)
        {
            lblErrorMessage.Text = string.Empty;
            try
            {
                LocationManager.SetFormLocation(this.Location);
                Form fBestScores = new BestScores(this.username);
                this.Hide();
                fBestScores.ShowDialog();
                this.Location = LocationManager.GetFormLocation();
                this.Show();
            }
            catch (Exception ex)
            {
                ChangeErrorText(ex.Message);
            }
        }

        private void ChangeErrorText(string message)
        {
            lblErrorMessage.Text = message;
            lblErrorMessage.Left = (this.Width - lblErrorMessage.Width - 20) / 2; //subtracting 20 to include the edge 
        }

        private void btnStatus_Click(object sender, EventArgs e)
        {
            lblErrorMessage.Text = string.Empty;
            try
            {
                LocationManager.SetFormLocation(this.Location);
                Form fStatus = new MyStatus(username);
                this.Hide();
                fStatus.ShowDialog();
                this.Location = LocationManager.GetFormLocation();
                this.Show();
            }
            catch (Exception ex)
            {
                ChangeErrorText(ex.Message);
            }
        }

        private void btnJoinRoom_Click(object sender, EventArgs e)
        {
            lblErrorMessage.Text = string.Empty;
            try
            {
                LocationManager.SetFormLocation(this.Location);
                Form fConnectToRoom = new ConnectToRoom();
                this.Hide();
                fConnectToRoom.ShowDialog();
                this.Location = LocationManager.GetFormLocation();
                this.Show();
            }
            catch (Exception ex)
            {
                ChangeErrorText(ex.Message);
            }
        }

        private void btnCreateRoom_Click(object sender, EventArgs e)
        {
            lblErrorMessage.Text = string.Empty;
            try
            {
                LocationManager.SetFormLocation(this.Location);
                Form fCreateRoom = new CreateRoom();
                this.Hide();
                fCreateRoom.ShowDialog();
                this.Location = LocationManager.GetFormLocation();
                this.Show();
            }
            catch (Exception ex)
            {
                ChangeErrorText(ex.Message);
            }
        }

        private void btnAddQuestion_Click(object sender, EventArgs e)
        {
            LocationManager.SetFormLocation(this.Location);
            Form fAddQuestion = new AddQuestion(this.username);
            this.Hide();
            fAddQuestion.ShowDialog();
            this.Location = LocationManager.GetFormLocation();
            this.Show();
        }

        private void btnHeadToHead_Click(object sender, EventArgs e)
        {
            DialogResult result = MessageBox.Show("This game includes 15 questions with 10 seconds for each question", "Head to Head", MessageBoxButtons.OKCancel,MessageBoxIcon.Information);
            if (result == DialogResult.OK)
            {
                LocationManager.SetFormLocation(this.Location);
                Form fHeadToHead = new HeadToHead();
                this.Hide();
                fHeadToHead.ShowDialog();
                this.Location = LocationManager.GetFormLocation();
                this.Show();
            }
        }
    }
}
