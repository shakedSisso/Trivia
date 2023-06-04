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
        public Menu(Point startLocation, string username)
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.Manual;
            this.Location = startLocation;
            lblUsername.Text = "Hello " + username + "!";
            this.username = username;
            lblUsername.Left = (this.Width - lblUsername.Width - 20) / 2;
            this.FormClosing += Menu_FormClosing;
        }

        private void Menu_FormClosing(object? sender, FormClosingEventArgs e)
        {
            try
            {
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
                Form fBestScores = new BestScores(this.Location);
                this.Hide();
                fBestScores.ShowDialog();
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
                Form fStatus = new MyStatus(this.Location, username);
                this.Hide();
                fStatus.ShowDialog();
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
                Form fConnectToRoom = new ConnectToRoom(this.Location);
                this.Hide();
                fConnectToRoom.ShowDialog();
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
                Form fCreateRoom = new CreateRoom(this.Location);
                this.Hide();
                fCreateRoom.ShowDialog();
                this.Show();
            }
            catch (Exception ex)
            {
                ChangeErrorText(ex.Message);
            }
        }
    }
}
