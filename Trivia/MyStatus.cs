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
    public partial class MyStatus : Form
    {
        public MyStatus(Point startLocation, string username)
        {
            InitializeComponent();
            gbStats.Text = username + "'s statistics";
            this.StartPosition = FormStartPosition.Manual;
            this.Location = startLocation;
            this.Text = gbStats.Text;
            try
            {
                string[] stats = Program.GetCommunicator().GetStatistics();
                if (stats[0] != "-nan(ind)")
                {
                    lblAverage.Text = stats[0];
                }
                else
                {
                    lblAverage.Text = "0.000";
                }
                lblAverage.Left = gbStats.Right - (lblAverage.Width + 80);
                lblRightAnswers.Text = stats[1];
                lblRightAnswers.Left = gbStats.Right - (lblRightAnswers.Width + 80);
                lblWrongAnswers.Text = stats[2];
                lblWrongAnswers.Left = gbStats.Right - (lblWrongAnswers.Width + 80);
                lblTotalGames.Text = stats[3];
                lblTotalGames.Left = gbStats.Right - (lblTotalGames.Width + 80);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                return;
            }
        }

        private void btnBack_Click(object sender, EventArgs e)
        {
            this.Dispose();
        }
    }
}
