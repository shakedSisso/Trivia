﻿using System;
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
            this.StartPosition = FormStartPosition.CenterScreen;
        }

        private void btnBack_Click(object sender, EventArgs e)
        {
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

                    Program.GetCommunicator().CreateRoom(name, playersCount, questionCount, timeOut);
                    Form fRoomAdmin = new RoomAdmin(name);
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

        private void btnBack_Click_1(object sender, EventArgs e)
        {
            this.Dispose();
        }
    }
}
