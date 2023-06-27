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
    public partial class AddQuestion : Form
    {
        private string[] questionWords = { "what", "who", "whom", "whose", "which", "where", "when", "why", "how" };
        private string author;
        private string question;
        private string correctAnswer;
        private string answer2;
        private string answer3;
        private string answer4;
        public AddQuestion(string author)
        {
            InitializeComponent();
            StartPosition = FormStartPosition.Manual;
            this.Location = LocationManager.GetFormLocation();
            this.author = author;
        }

        private void btnAddQuestion_Click(object sender, EventArgs e)
        {
            if (tbQuestion.Text == string.Empty || tbAnswer1.Text == string.Empty ||
                tbAnswer2.Text == string.Empty || tbAnswer3.Text == string.Empty ||
                tbAnswer4.Text == string.Empty || !IsRadioButtonChecked())
            {
                ChangeErrorText("Please make sure you filled all the fields");

            }
            else
            {
                try
                {
                    question = tbQuestion.Text;
                    string firstWord = question.Split(' ', StringSplitOptions.RemoveEmptyEntries).FirstOrDefault()?.ToLower();

                    bool startsWithQuestionWord = questionWords.Contains(firstWord);

                    if (!question.EndsWith('?'))
                    {
                        throw new Exception("Question must include \'?\' in the end");
                    }
                    if (!startsWithQuestionWord)
                    {
                        throw new Exception("Question must start with a question word");
                    }
                    switch (GetCorrectAnswerId())
                    {
                        case 1:
                            correctAnswer = tbAnswer1.Text;
                            answer2 = tbAnswer2.Text;
                            answer3 = tbAnswer3.Text;
                            answer4 = tbAnswer4.Text;
                            break;
                        case 2:
                            correctAnswer = tbAnswer2.Text;
                            answer2 = tbAnswer1.Text;
                            answer3 = tbAnswer3.Text;
                            answer4 = tbAnswer4.Text;
                            break;
                        case 3:
                            correctAnswer = tbAnswer3.Text;
                            answer2 = tbAnswer2.Text;
                            answer3 = tbAnswer1.Text;
                            answer4 = tbAnswer4.Text;
                            break;
                        case 4:
                            correctAnswer = tbAnswer4.Text;
                            answer2 = tbAnswer2.Text;
                            answer3 = tbAnswer3.Text;
                            answer4 = tbAnswer1.Text;
                            break;
                        default:
                            throw new Exception("An error occured");
                    }
                    Program.GetCommunicator().AddQuestion(this.author, question, correctAnswer, answer2, answer3, answer4);
                    MessageBox.Show("Question added, thank you", "Added", MessageBoxButtons.OK);
                    LocationManager.SetFormLocation(this.Location);
                    this.Dispose();
                }
                catch (Exception ex)
                {
                    ChangeErrorText(ex.Message);
                }
            }
        }

        private int GetCorrectAnswerId()
        {
            if (rbAnswer1.Checked)
            {
                return 1;
            }
            else if (rbAnswer2.Checked)
            {
                return 2;
            }
            else if (rbAnswer3.Checked)
            {
                return 3;
            }
            return 4; //checked if a radio button is checked before so 4 is the default option
        }

        private bool IsRadioButtonChecked()
        {
            foreach (Control control in this.Controls)
            {
                if (control is RadioButton rb && rb.Checked)
                {
                    return true;
                }
            }
            return false;
        }

        private void ChangeErrorText(string message)
        {
            lblErrorMessage.Text = message;
            lblErrorMessage.Left = (this.Width - lblErrorMessage.Width - 20) / 2; //subtracting 20 to include the edge 
        }

        private void btnBack_Click(object sender, EventArgs e)
        {
            LocationManager.SetFormLocation(this.Location);
            this.Dispose();
        }
    }
}
