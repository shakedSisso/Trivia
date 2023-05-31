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
        public BestScores()
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.CenterScreen;
            lblFirstPlace.Text = string.Empty;
            lblSecondPlace.Text = string.Empty;
            lblThirdPlace.Text = string.Empty;
            lblFourthPlace.Text = string.Empty;
            lblFifthPlace.Text = string.Empty;
            try
            {
                string[] highScores = Program.GetCommunicator().GetHighScores();
                lblFirstPlace.Text = highScores[0];
                lblSecondPlace.Text = highScores[1];
                lblThirdPlace.Text = highScores[2];
                lblFourthPlace.Text = highScores[3];
                lblFifthPlace.Text = highScores[4];
            }
            catch (Exception ex)
            {
                throw new Exception(ex.Message);
            }

        }

        private void btnBack_Click(object sender, EventArgs e)
        {
            this.Dispose();
        }
    }
}
