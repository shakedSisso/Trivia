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
                int len = highScores.Length;
                if (len == 5)
                    lblFifthPlace.Text = highScores[4];
                if (len == 4)
                    lblFourthPlace.Text = highScores[3];
                if (len == 3)
                    lblThirdPlace.Text = highScores[2];
                if (len == 2)
                    lblSecondPlace.Text = highScores[1];
                if (len == 1)
                    lblFirstPlace.Text = highScores[0];
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
