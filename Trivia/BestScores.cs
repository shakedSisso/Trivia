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
    public partial class BestScores : Form
    {
        public BestScores(string username)
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.Manual;
            this.Location = LocationManager.GetFormLocation();
            lblFirstPlace.Text = string.Empty;
            lblSecondPlace.Text = string.Empty;
            lblThirdPlace.Text = string.Empty;
            lblFourthPlace.Text = string.Empty;
            lblFifthPlace.Text = string.Empty;
            try
            {
                int currectX;
                string[] highScores = Program.GetCommunicator().GetHighScores();
                int len = highScores.Length;
                if (len >= 5)
                {
                    lblFifthPlace.Text = highScores[4];
                }
                if (len >= 4)
                {
                    lblFourthPlace.Text = highScores[3];
                }
                if (len >= 3)
                {
                    currectX = lblThirdPlace.Left;
                    lblThirdPlace.Text = highScores[2];
                    lblThirdPlace.Left = currectX - lblThirdPlace.Width / 2;
                }
                if (len >= 2)
                {
                    currectX = lblSecondPlace.Left;
                    lblSecondPlace.Text = highScores[1];
                    lblSecondPlace.Left = currectX - lblSecondPlace.Width / 2;
                }
                if (len >= 1)
                {
                    currectX = lblFirstPlace.Left;
                    lblFirstPlace.Text = highScores[0];
                    lblFirstPlace.Left = currectX - lblFirstPlace.Width / 2;
                }
                foreach (Control control in this.Controls)
                {
                    if (control is Label lbl && lbl != lblTopFive)
                    {
                        if (lbl.Text.IndexOf(username + "- ") != -1)
                        {
                            lbl.BackColor = Color.DarkSlateGray;
                            lbl.ForeColor = Color.Honeydew;
                            lbl.BorderStyle = BorderStyle.FixedSingle;
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                throw new Exception(ex.Message);
            }

        }

        private void btnBack_Click(object sender, EventArgs e)
        {
            LocationManager.SetFormLocation(this.Location);
            this.Dispose();
        }
    }
}
