namespace Trivia
{
    partial class Game
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Game));
            lblQuestionCount = new Label();
            lblRoomName = new Label();
            pictureBox1 = new PictureBox();
            lblQuestion = new Label();
            btnAnswer1 = new Button();
            btnAnswer2 = new Button();
            btnAnswer3 = new Button();
            btnAnswer4 = new Button();
            lblTimeOut = new Label();
            lblScore = new Label();
            label1 = new Label();
            btnExit = new Button();
            tmrCountdown = new System.Windows.Forms.Timer(components);
            ((System.ComponentModel.ISupportInitialize)pictureBox1).BeginInit();
            SuspendLayout();
            // 
            // lblQuestionCount
            // 
            lblQuestionCount.AutoSize = true;
            lblQuestionCount.Font = new Font("Bauhaus 93", 20F, FontStyle.Regular, GraphicsUnit.Point);
            lblQuestionCount.ForeColor = Color.DarkSlateGray;
            lblQuestionCount.Location = new Point(269, 55);
            lblQuestionCount.Name = "lblQuestionCount";
            lblQuestionCount.Size = new Size(207, 39);
            lblQuestionCount.TabIndex = 45;
            lblQuestionCount.Text = "Question x/y";
            // 
            // lblRoomName
            // 
            lblRoomName.AutoSize = true;
            lblRoomName.Font = new Font("Bauhaus 93", 16F, FontStyle.Regular, GraphicsUnit.Point);
            lblRoomName.ForeColor = Color.DarkSlateGray;
            lblRoomName.Location = new Point(335, 25);
            lblRoomName.Name = "lblRoomName";
            lblRoomName.Size = new Size(80, 30);
            lblRoomName.TabIndex = 46;
            lblRoomName.Text = "name";
            // 
            // pictureBox1
            // 
            pictureBox1.BackColor = Color.LightCyan;
            pictureBox1.Location = new Point(90, 107);
            pictureBox1.Name = "pictureBox1";
            pictureBox1.Size = new Size(600, 285);
            pictureBox1.TabIndex = 47;
            pictureBox1.TabStop = false;
            // 
            // lblQuestion
            // 
            lblQuestion.AutoSize = true;
            lblQuestion.BackColor = Color.LightCyan;
            lblQuestion.Font = new Font("Segoe UI", 13F, FontStyle.Italic, GraphicsUnit.Point);
            lblQuestion.Location = new Point(106, 119);
            lblQuestion.Name = "lblQuestion";
            lblQuestion.Size = new Size(103, 30);
            lblQuestion.TabIndex = 48;
            lblQuestion.Text = "question?";
            // 
            // btnAnswer1
            // 
            btnAnswer1.BackColor = Color.MintCream;
            btnAnswer1.Cursor = Cursors.Hand;
            btnAnswer1.Font = new Font("Maiandra GD", 10.8F, FontStyle.Bold, GraphicsUnit.Point);
            btnAnswer1.Location = new Point(110, 190);
            btnAnswer1.Name = "btnAnswer1";
            btnAnswer1.Size = new Size(558, 35);
            btnAnswer1.TabIndex = 49;
            btnAnswer1.Text = "answer1";
            btnAnswer1.UseVisualStyleBackColor = false;
            btnAnswer1.Click += SharedButtonClick;
            // 
            // btnAnswer2
            // 
            btnAnswer2.BackColor = Color.MintCream;
            btnAnswer2.Cursor = Cursors.Hand;
            btnAnswer2.Font = new Font("Maiandra GD", 10.8F, FontStyle.Bold, GraphicsUnit.Point);
            btnAnswer2.Location = new Point(110, 237);
            btnAnswer2.Name = "btnAnswer2";
            btnAnswer2.Size = new Size(558, 35);
            btnAnswer2.TabIndex = 50;
            btnAnswer2.Text = "answer2";
            btnAnswer2.UseVisualStyleBackColor = false;
            btnAnswer2.Click += SharedButtonClick;
            // 
            // btnAnswer3
            // 
            btnAnswer3.BackColor = Color.MintCream;
            btnAnswer3.Cursor = Cursors.Hand;
            btnAnswer3.Font = new Font("Maiandra GD", 10.8F, FontStyle.Bold, GraphicsUnit.Point);
            btnAnswer3.Location = new Point(110, 289);
            btnAnswer3.Name = "btnAnswer3";
            btnAnswer3.Size = new Size(558, 35);
            btnAnswer3.TabIndex = 51;
            btnAnswer3.Text = "answer3";
            btnAnswer3.UseVisualStyleBackColor = false;
            btnAnswer3.Click += SharedButtonClick;
            // 
            // btnAnswer4
            // 
            btnAnswer4.BackColor = Color.MintCream;
            btnAnswer4.Cursor = Cursors.Hand;
            btnAnswer4.Font = new Font("Maiandra GD", 10.8F, FontStyle.Bold, GraphicsUnit.Point);
            btnAnswer4.Location = new Point(110, 337);
            btnAnswer4.Name = "btnAnswer4";
            btnAnswer4.Size = new Size(558, 35);
            btnAnswer4.TabIndex = 52;
            btnAnswer4.Text = "answer4";
            btnAnswer4.UseVisualStyleBackColor = false;
            btnAnswer4.Click += SharedButtonClick;
            // 
            // lblTimeOut
            // 
            lblTimeOut.AutoSize = true;
            lblTimeOut.Font = new Font("Segoe UI Semibold", 16.2F, FontStyle.Bold, GraphicsUnit.Point);
            lblTimeOut.Location = new Point(720, 25);
            lblTimeOut.Name = "lblTimeOut";
            lblTimeOut.Size = new Size(49, 38);
            lblTimeOut.TabIndex = 53;
            lblTimeOut.Text = "00";
            // 
            // lblScore
            // 
            lblScore.AutoSize = true;
            lblScore.Font = new Font("Segoe UI Semibold", 16.2F, FontStyle.Bold, GraphicsUnit.Point);
            lblScore.Location = new Point(128, 25);
            lblScore.Name = "lblScore";
            lblScore.Size = new Size(61, 38);
            lblScore.TabIndex = 54;
            lblScore.Text = "0/0";
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Segoe UI Semibold", 16.2F, FontStyle.Bold, GraphicsUnit.Point);
            label1.Location = new Point(28, 25);
            label1.Name = "label1";
            label1.Size = new Size(94, 38);
            label1.TabIndex = 55;
            label1.Text = "Score:";
            // 
            // btnExit
            // 
            btnExit.BackColor = Color.CadetBlue;
            btnExit.Cursor = Cursors.Hand;
            btnExit.Font = new Font("Maiandra GD", 9F, FontStyle.Bold, GraphicsUnit.Point);
            btnExit.ForeColor = SystemColors.ButtonHighlight;
            btnExit.Location = new Point(640, 409);
            btnExit.Name = "btnExit";
            btnExit.Size = new Size(148, 29);
            btnExit.TabIndex = 56;
            btnExit.Text = "exit";
            btnExit.UseVisualStyleBackColor = false;
            btnExit.Click += btnExit_Click;
            // 
            // tmrCountdown
            // 
            tmrCountdown.Interval = 1000;
            tmrCountdown.Tick += tmrCountdown_Tick;
            // 
            // Game
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = Color.PaleTurquoise;
            ClientSize = new Size(800, 450);
            Controls.Add(btnExit);
            Controls.Add(label1);
            Controls.Add(lblScore);
            Controls.Add(lblTimeOut);
            Controls.Add(btnAnswer4);
            Controls.Add(btnAnswer3);
            Controls.Add(btnAnswer2);
            Controls.Add(btnAnswer1);
            Controls.Add(lblQuestion);
            Controls.Add(lblRoomName);
            Controls.Add(lblQuestionCount);
            Controls.Add(pictureBox1);
            Icon = (Icon)resources.GetObject("$this.Icon");
            Name = "Game";
            Text = "Game";
            FormClosing += Game_FormClosing;
            ((System.ComponentModel.ISupportInitialize)pictureBox1).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label lblQuestionCount;
        private Label lblRoomName;
        private PictureBox pictureBox1;
        private Label lblQuestion;
        private Button btnAnswer1;
        private Button btnAnswer2;
        private Button btnAnswer3;
        private Button btnAnswer4;
        private Label lblTimeOut;
        private Label lblScore;
        private Label label1;
        private Button btnExit;
        private System.Windows.Forms.Timer tmrCountdown;
    }
}