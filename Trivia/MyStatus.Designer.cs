namespace Trivia
{
    partial class MyStatus
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MyStatus));
            btnBack = new Button();
            gbStats = new GroupBox();
            lblAverage = new Label();
            lblWrongAnswers = new Label();
            lblRightAnswers = new Label();
            lblTotalGames = new Label();
            label3 = new Label();
            label2 = new Label();
            label4 = new Label();
            label1 = new Label();
            gbStats.SuspendLayout();
            SuspendLayout();
            // 
            // btnBack
            // 
            btnBack.BackColor = Color.CadetBlue;
            btnBack.Font = new Font("Maiandra GD", 9F, FontStyle.Bold, GraphicsUnit.Point);
            btnBack.ForeColor = SystemColors.ButtonHighlight;
            btnBack.Location = new Point(640, 409);
            btnBack.Name = "btnBack";
            btnBack.Size = new Size(148, 29);
            btnBack.TabIndex = 21;
            btnBack.Text = "back";
            btnBack.UseVisualStyleBackColor = false;
            btnBack.Click += btnBack_Click;
            // 
            // gbStats
            // 
            gbStats.BackColor = Color.LightCyan;
            gbStats.Controls.Add(lblAverage);
            gbStats.Controls.Add(lblWrongAnswers);
            gbStats.Controls.Add(lblRightAnswers);
            gbStats.Controls.Add(lblTotalGames);
            gbStats.Controls.Add(label3);
            gbStats.Controls.Add(label2);
            gbStats.Controls.Add(label4);
            gbStats.Controls.Add(label1);
            gbStats.Font = new Font("Bauhaus 93", 15F, FontStyle.Bold | FontStyle.Underline, GraphicsUnit.Point);
            gbStats.Location = new Point(76, 42);
            gbStats.Name = "gbStats";
            gbStats.Size = new Size(643, 342);
            gbStats.TabIndex = 22;
            gbStats.TabStop = false;
            gbStats.Text = "User's Stats";
            // 
            // lblAverage
            // 
            lblAverage.AutoSize = true;
            lblAverage.Font = new Font("Maiandra GD", 12F, FontStyle.Regular, GraphicsUnit.Point);
            lblAverage.Location = new Point(536, 286);
            lblAverage.Name = "lblAverage";
            lblAverage.Size = new Size(76, 24);
            lblAverage.TabIndex = 9;
            lblAverage.Text = "00.000";
            // 
            // lblWrongAnswers
            // 
            lblWrongAnswers.AutoSize = true;
            lblWrongAnswers.Font = new Font("Maiandra GD", 12F, FontStyle.Regular, GraphicsUnit.Point);
            lblWrongAnswers.Location = new Point(567, 205);
            lblWrongAnswers.Name = "lblWrongAnswers";
            lblWrongAnswers.Size = new Size(34, 24);
            lblWrongAnswers.TabIndex = 8;
            lblWrongAnswers.Text = "00";
            // 
            // lblRightAnswers
            // 
            lblRightAnswers.AutoSize = true;
            lblRightAnswers.Font = new Font("Maiandra GD", 12F, FontStyle.Regular, GraphicsUnit.Point);
            lblRightAnswers.Location = new Point(567, 135);
            lblRightAnswers.Name = "lblRightAnswers";
            lblRightAnswers.Size = new Size(34, 24);
            lblRightAnswers.TabIndex = 7;
            lblRightAnswers.Text = "00";
            // 
            // lblTotalGames
            // 
            lblTotalGames.AutoSize = true;
            lblTotalGames.Font = new Font("Maiandra GD", 12F, FontStyle.Regular, GraphicsUnit.Point);
            lblTotalGames.Location = new Point(567, 61);
            lblTotalGames.Name = "lblTotalGames";
            lblTotalGames.Size = new Size(34, 24);
            lblTotalGames.TabIndex = 6;
            lblTotalGames.Text = "00";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Font = new Font("Maiandra GD", 12F, FontStyle.Bold, GraphicsUnit.Point);
            label3.Location = new Point(8, 286);
            label3.Name = "label3";
            label3.Size = new Size(261, 24);
            label3.TabIndex = 5;
            label3.Text = "Average time for answer: ";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Font = new Font("Maiandra GD", 12F, FontStyle.Bold, GraphicsUnit.Point);
            label2.Location = new Point(8, 135);
            label2.Name = "label2";
            label2.Size = new Size(263, 24);
            label2.TabIndex = 4;
            label2.Text = "Number of right answers: ";
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Font = new Font("Maiandra GD", 12F, FontStyle.Bold, GraphicsUnit.Point);
            label4.Location = new Point(6, 205);
            label4.Name = "label4";
            label4.Size = new Size(279, 24);
            label4.TabIndex = 3;
            label4.Text = "Number of wrong answers: ";
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Maiandra GD", 12F, FontStyle.Bold, GraphicsUnit.Point);
            label1.Location = new Point(8, 61);
            label1.Name = "label1";
            label1.Size = new Size(195, 24);
            label1.TabIndex = 0;
            label1.Text = "Number of games: ";
            // 
            // MyStatus
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = Color.PaleTurquoise;
            ClientSize = new Size(800, 450);
            Controls.Add(gbStats);
            Controls.Add(btnBack);
            Icon = (Icon)resources.GetObject("$this.Icon");
            Name = "MyStatus";
            Text = "MyStatus";
            gbStats.ResumeLayout(false);
            gbStats.PerformLayout();
            ResumeLayout(false);
        }

        #endregion

        private Button btnBack;
        private GroupBox gbStats;
        private Label label4;
        private Label label1;
        private Label label2;
        private Label lblAverage;
        private Label lblWrongAnswers;
        private Label lblRightAnswers;
        private Label lblTotalGames;
        private Label label3;
    }
}