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
        private bool gotScores;
        private dynamic results;
        public GameScores(Form owner)
        {
            InitializeComponent();
            StartPosition = FormStartPosition.Manual;
            this.Location = LocationManager.GetFormLocation();
            this.Owner = owner;
            dynamic playerResults;
            try
            {
                playerResults = Program.GetCommunicator().GetGameResults();
            }
            catch (Exception ex)
            {
                throw new Exception(ex.Message);
            }
            this.results = playerResults;
            if (!ShowResults())
            {
                gotScores = false;
                tmrShowResult.Start();
            }
        }

        private bool ShowResults()
        {
            for (int i = this.Controls.Count - 1; i >= 0; i--)
            {
                if (this.Controls[i] is Label label)
                {
                    this.Controls.RemoveAt(i);
                    label.Dispose();
                }
            }
            try
            {
                results = Program.GetCommunicator().GetGameResults();
            }
            catch (Exception ex)
            {
                throw new Exception(ex.Message);
            }
            if (results == null)
            {
                Label lblError = new Label();
                lblError.Text = "Game isn't over";
                lblError.Font = new Font("Maiandra GD", 20, FontStyle.Bold);
                lblError.ForeColor = Color.Maroon;
                lblError.Width = lblError.Text.Length * 20;
                lblError.Top = 10;
                lblError.Height = 45;
                this.Controls.Add(lblError);
                ResizeAndRelocateForm();
                return false;
            }
            foreach (dynamic result in results.results)
            {
                Label lblResult = new Label();
                lblResult.Height = 45;
                string username = "Username: " + result.username;
                string score = "Score: " + result.correctAnswerCount;
                lblResult.Text = username + "   " + score;
                lblResult.Width = (username + score).Length * 20;
                lblResult.Top = count * 45;
                lblResult.Font = new Font("Maiandra GD", 20, FontStyle.Bold);
                lblResult.ForeColor = Color.Black;
                this.Controls.Add(lblResult);
                count++;
            }
            ResizeAndRelocateForm();
            return true;
        }

        private void ResizeAndRelocateForm()
        {
            int maxLabelWidth = 0;
            int maxLabelHeight = 0;

            foreach (Control control in this.Controls)
            {
                // Get the size of the label
                Size labelSize = control.Size;

                // Update the maximum label width and height if necessary
                maxLabelWidth = Math.Max(maxLabelWidth, labelSize.Width);
                maxLabelHeight += labelSize.Height;
            }

            // Resize the form based on the largest label size
            this.Size = new Size(maxLabelWidth + 25, maxLabelHeight + 75);

            Form parentForm = Owner;
            if (parentForm != null)
            {
                int parentFormX = parentForm.Location.X;
                int parentFormY = parentForm.Location.Y;
                int parentFormWidth = parentForm.Width;
                int parentFormHeight = parentForm.Height;

                int formToMoveWidth = this.Width;
                int formToMoveHeight = this.Height;

                int formToMoveX = parentFormX + (parentFormWidth - formToMoveWidth) / 2;
                int formToMoveY = parentFormY + (parentFormHeight - formToMoveHeight) / 2;

                this.Location = new Point(formToMoveX, formToMoveY);
            }
        }

        private void tmrShowResult_Tick(object sender, EventArgs e)
        {
            if (!gotScores)
            {
                try
                {
                    gotScores = ShowResults();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
            else
            {
                tmrShowResult.Stop();
            }
        }
    }
}
