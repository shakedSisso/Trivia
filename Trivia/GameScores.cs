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
    public partial class GameScores : Form
    {
        int count = 0;
        private dynamic results;
        public GameScores()
        {
            InitializeComponent();

            dynamic playerResults;
            try
            {
                results = Program.GetCommunicator().GetGameResults();
                ShowResults();
            }
            catch (Exception ex)
            {
                throw new Exception(ex.Message);
            }
        }

        private void ShowResults()
        {
            if (results.status == (int)Communicator.codes.GetQuestionFailed)
            {
                Label lblError = new Label();
                lblError.Text = "Game isn't over";
                lblError.Font = new Font("Segoe UI", 40F, FontStyle.Bold, GraphicsUnit.Point);
                lblError.ForeColor = Color.Maroon;
                lblError.Left = (this.Width - lblError.Left) / 2;
                lblError.Top = (this.Height - lblError.Top) / 2;
                this.Controls.Add(lblError);
                try
                {
                    results = Program.GetCommunicator().GetGameResults();
                    ShowResults();
                }
                catch (Exception ex)
                {
                    throw new Exception(ex.Message);
                }
            }
            else
            {
                foreach (dynamic result in results)
                {
                    Label lblResult = new Label();
                    lblResult.Text = "Username: " + result.username + " Score: " + result.correctAnswerCount;
                    lblResult.Top = this.Top + count * 50 + 50;
                    lblResult.Left = this.Left + 50;
                    lblResult.Font = new Font("Segoe UI", 40F, FontStyle.Bold, GraphicsUnit.Point);
                    this.Controls.Add(lblResult);
                }
            }
        }
    }
}
