using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Trivia
{
    public partial class Game : Form
    {
        private const int QUESTION_LENGTH = 55;
        private const int TIME_OUT = 999;
        private string roomName;
        private int questionTimeOut;
        private int remainingSeconds;
        private int questionCount;
        private int currentCount;
        private int correctAnswers;
        private object communicatorLock;
        private bool isLocked;
        private bool nextQuestion;
        private System.Threading.Timer timer;
        private dynamic question;
        public Game(string name, int questionTimeOut, int questionCount)
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.Manual;
            this.Location = LocationManager.GetFormLocation();
            this.Text = name;
            this.roomName = name;
            this.questionTimeOut = questionTimeOut;
            this.questionCount = questionCount;
            this.communicatorLock = new object();
            this.isLocked = false;
            this.nextQuestion = true;
            try
            {
                InitButtons();
                CreateScreen();
                timer = new System.Threading.Timer(ResetScreen, null, 0, 1000);
            }
            catch (Exception ex)
            {
                throw new Exception(ex.Message);
            }
        }

        private void InitButtons()
        {
            btnAnswer1.Tag = 1;
            btnAnswer2.Tag = 2;
            btnAnswer3.Tag = 3;
            btnAnswer4.Tag = 4;
        }

        private void ChangeScore()
        {
            lblScore.Text = correctAnswers.ToString() + " / " + currentCount.ToString();
        }

        private void CreateScreen()
        {
            currentCount = 1;
            ChangeScore();
            try
            {
                lock (communicatorLock)
                {
                    isLocked = true;
                    question = Program.GetCommunicator().GetQuestion();
                    isLocked = false;
                }
                if (question != null && question.question != "")
                {
                    
                    NextQuestion();
                }
                else
                {
                    OpenGameScoresForm();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void ResetScreen(object state)
        {
            if (this.IsHandleCreated && nextQuestion)
            {
                nextQuestion = false;
                currentCount++;
                this.Invoke((MethodInvoker)delegate
                {
                    ChangeScore();
                }); 
                lock (communicatorLock)
                {
                    isLocked = true;
                    question = Program.GetCommunicator().GetQuestion();
                    isLocked = false;
                }
                if (question != null && question.question != "")
                {
                    this.Invoke((MethodInvoker)delegate
                    {
                        NextQuestion();
                    });
                }
                else
                {
                    this.Invoke((MethodInvoker)delegate
                    {
                        OpenGameScoresForm();
                    });
                }

            }
        }

        private void OpenGameScoresForm()
        {
            try
            {
                nextQuestion = false;
                LocationManager.SetFormLocation(this.Location);
                Form fGameScores = new GameScores(this);
                if (timer != null)
                {
                    this.timer.Dispose();
                    this.timer = null;
                }
                fGameScores.ShowDialog();
                this.Dispose();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void NextQuestion()
        {
            this.remainingSeconds = questionTimeOut;
            lblTimeOut.Text = remainingSeconds.ToString();
            tmrCountdown.Start();
            foreach (Control control in this.Controls)
            {
                if (control is Button button && button != btnExit)
                {
                    control.BackColor = Color.MintCream;
                    control.Enabled = true;
                }
            }
            nextQuestion = false;
            GetQuestion();
        }

        private void GetQuestion()
        {
            string q = question.question;

            int charsPerLine = QUESTION_LENGTH;
            int currentIndex = charsPerLine;

            while (currentIndex < q.Length)
            {
                int spaceIndex = q.LastIndexOf(' ', currentIndex, charsPerLine);

                if (spaceIndex != -1)
                {
                    q = q.Remove(spaceIndex, 1).Insert(spaceIndex, "\n");
                    currentIndex = spaceIndex + charsPerLine + 1;
                }
                else
                {
                    currentIndex += charsPerLine;
                }
            }
            lblQuestion.Text = q;
            lblQuestionCount.Text = "Question " + currentCount.ToString() + "/" + questionCount.ToString();
            dynamic answers = question.answers.First;
            btnAnswer1.Text = answers["1"];
            btnAnswer2.Text = answers["2"];
            btnAnswer3.Text = answers["3"];
            btnAnswer4.Text = answers["4"];
        }

        private void SharedButtonClick(object sender, EventArgs e)
        {
            this.tmrCountdown.Stop();
            Button button = (Button)sender;
            int answerId = (int)button.Tag;
            int answerTime = questionTimeOut - remainingSeconds;
            try
            {
                int correctAnswer = Program.GetCommunicator().SubmitAnswer(answerId, answerTime);
                if (correctAnswer == answerId)
                {
                    button.BackColor = Color.PaleGreen;
                    correctAnswers++;
                    foreach (Control control in this.Controls)
                    {
                        if (control is Button btn && btn != btnExit)
                        {
                            btn.Enabled = false;
                        }
                    }
                }
                else
                {
                    foreach (Control control in this.Controls)
                    {
                        if (control is Button btn && btn != btnExit)
                        {
                            btn.BackColor = Color.IndianRed;
                            btn.Enabled = false;
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            nextQuestion = true;
        }

        private void tmrCountdown_Tick(object sender, EventArgs e)
        {
            remainingSeconds--;
            lblTimeOut.Text = remainingSeconds.ToString();

            if (remainingSeconds <= 0)
            {
                foreach (Control control in this.Controls)
                {
                    if (control is Button btn && btn != btnExit)
                    {
                        btn.BackColor = Color.IndianRed;
                        btn.Enabled = false;
                    }
                }
                Program.GetCommunicator().SubmitAnswer(TIME_OUT, questionTimeOut);
                nextQuestion = true;
                tmrCountdown.Stop();
            }
        }

        private void btnExit_Click(object sender, EventArgs e)
        {
            this.Dispose();
        }

        private void Game_FormClosing(object sender, FormClosingEventArgs e)
        {
            try
            {
                LocationManager.SetFormLocation(this.Location);
                Program.GetCommunicator().LeaveGame();
                if (this.timer != null)
                {
                    this.timer.Dispose();
                    this.timer = null;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }
}
