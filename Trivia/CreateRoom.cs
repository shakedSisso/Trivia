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
    public partial class CreateRoom : Form
    {
        public CreateRoom()
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.Manual;
            this.Location = LocationManager.GetFormLocation();
        }

        private void btnBack_Click(object sender, EventArgs e)
        {
            LocationManager.SetFormLocation(this.Location);
            this.Dispose();
        }

        private void btnCreateRoom_Click(object sender, EventArgs e)
        {
            if (tbRoomName.Text != string.Empty && tbNumOfPlayers.Text != string.Empty
                && tbNumOfQuestions.Text != string.Empty && tbTimeForQuestions.Text != string.Empty)
            {
                try
                {
                    string name = tbRoomName.Text;
                    int playersCount = int.Parse(tbNumOfPlayers.Text);
                    int questionCount = int.Parse(tbNumOfQuestions.Text);
                    int timeOut = int.Parse(tbTimeForQuestions.Text);
                    bool includeUserQuestions = cbIncludeUserQuestion.Checked;

                    Program.GetCommunicator().CreateRoom(name, playersCount, questionCount, timeOut, includeUserQuestions);
                    LocationManager.SetFormLocation(this.Location);
                    Form fRoomAdmin = new RoomAdmin(name, playersCount);
                    this.Hide();
                    fRoomAdmin.ShowDialog();
                    this.Dispose();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            else
            {
                ChangeErrorText("Please fill all fields");
            }
        }

        private void ChangeErrorText(string message)
        {
            lblErrorMessage.Text = message;
            lblErrorMessage.Left = (this.Width - lblErrorMessage.Width - 20) / 2; //subtracting 20 to include the edge 
        }

        private void cbIncludeUserQuestion_CheckedChanged(object sender, EventArgs e)
        {
            if (cbIncludeUserQuestion.Checked)
            {
                DialogResult result = MessageBox.Show("Those questions were written by users so they might include:\n* bad language\n* personal opinions\n* politics\n* religion\n* sexuality", "Are you sure?", MessageBoxButtons.YesNo, MessageBoxIcon.Warning);
                if (result == DialogResult.Yes)
                {
                    cbIncludeUserQuestion.Checked = true;
                }
                else
                {
                    cbIncludeUserQuestion.Checked = false;
                }
            }
        }
    }
}
