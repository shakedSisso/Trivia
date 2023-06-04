namespace Trivia
{
    partial class BestScores
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(BestScores));
            btnBack = new Button();
            pictureBox1 = new PictureBox();
            pictureBox2 = new PictureBox();
            pictureBox3 = new PictureBox();
            lblFourthPlace = new Label();
            lblFifthPlace = new Label();
            lblThirdPlace = new Label();
            lblSecondPlace = new Label();
            lblFirstPlace = new Label();
            label2 = new Label();
            ((System.ComponentModel.ISupportInitialize)pictureBox1).BeginInit();
            ((System.ComponentModel.ISupportInitialize)pictureBox2).BeginInit();
            ((System.ComponentModel.ISupportInitialize)pictureBox3).BeginInit();
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
            // pictureBox1
            // 
            pictureBox1.Image = (Image)resources.GetObject("pictureBox1.Image");
            pictureBox1.Location = new Point(107, 106);
            pictureBox1.Name = "pictureBox1";
            pictureBox1.Size = new Size(576, 196);
            pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBox1.TabIndex = 22;
            pictureBox1.TabStop = false;
            // 
            // pictureBox2
            // 
            pictureBox2.Image = (Image)resources.GetObject("pictureBox2.Image");
            pictureBox2.Location = new Point(462, 308);
            pictureBox2.Name = "pictureBox2";
            pictureBox2.Size = new Size(105, 72);
            pictureBox2.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBox2.TabIndex = 23;
            pictureBox2.TabStop = false;
            // 
            // pictureBox3
            // 
            pictureBox3.Image = (Image)resources.GetObject("pictureBox3.Image");
            pictureBox3.Location = new Point(171, 308);
            pictureBox3.Name = "pictureBox3";
            pictureBox3.Size = new Size(105, 72);
            pictureBox3.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBox3.TabIndex = 24;
            pictureBox3.TabStop = false;
            // 
            // lblFourthPlace
            // 
            lblFourthPlace.AutoSize = true;
            lblFourthPlace.Font = new Font("Maiandra GD", 15F, FontStyle.Regular, GraphicsUnit.Point);
            lblFourthPlace.Location = new Point(255, 329);
            lblFourthPlace.Name = "lblFourthPlace";
            lblFourthPlace.Size = new Size(81, 30);
            lblFourthPlace.TabIndex = 25;
            lblFourthPlace.Text = "fourth";
            // 
            // lblFifthPlace
            // 
            lblFifthPlace.AutoSize = true;
            lblFifthPlace.Font = new Font("Maiandra GD", 15F, FontStyle.Regular, GraphicsUnit.Point);
            lblFifthPlace.Location = new Point(544, 329);
            lblFifthPlace.Name = "lblFifthPlace";
            lblFifthPlace.Size = new Size(57, 30);
            lblFifthPlace.TabIndex = 26;
            lblFifthPlace.Text = "fifth";
            // 
            // lblThirdPlace
            // 
            lblThirdPlace.AutoSize = true;
            lblThirdPlace.Font = new Font("Maiandra GD", 15F, FontStyle.Regular, GraphicsUnit.Point);
            lblThirdPlace.Location = new Point(570, 163);
            lblThirdPlace.Name = "lblThirdPlace";
            lblThirdPlace.Size = new Size(64, 30);
            lblThirdPlace.TabIndex = 27;
            lblThirdPlace.Text = "third";
            // 
            // lblSecondPlace
            // 
            lblSecondPlace.AutoSize = true;
            lblSecondPlace.Font = new Font("Maiandra GD", 15F, FontStyle.Regular, GraphicsUnit.Point);
            lblSecondPlace.Location = new Point(219, 149);
            lblSecondPlace.Name = "lblSecondPlace";
            lblSecondPlace.Size = new Size(88, 30);
            lblSecondPlace.TabIndex = 28;
            lblSecondPlace.Text = "second";
            // 
            // lblFirstPlace
            // 
            lblFirstPlace.AutoSize = true;
            lblFirstPlace.Font = new Font("Maiandra GD", 15F, FontStyle.Bold, GraphicsUnit.Point);
            lblFirstPlace.ForeColor = SystemColors.ActiveCaptionText;
            lblFirstPlace.Location = new Point(393, 100);
            lblFirstPlace.Name = "lblFirstPlace";
            lblFirstPlace.Size = new Size(63, 30);
            lblFirstPlace.TabIndex = 29;
            lblFirstPlace.Text = "First";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Font = new Font("Bauhaus 93", 25F, FontStyle.Regular, GraphicsUnit.Point);
            label2.ForeColor = Color.DarkSlateGray;
            label2.Location = new Point(323, 29);
            label2.Name = "label2";
            label2.Size = new Size(124, 48);
            label2.TabIndex = 30;
            label2.Text = "Top 5";
            // 
            // BestScores
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = Color.PaleTurquoise;
            ClientSize = new Size(800, 450);
            Controls.Add(label2);
            Controls.Add(lblFirstPlace);
            Controls.Add(lblSecondPlace);
            Controls.Add(lblThirdPlace);
            Controls.Add(lblFifthPlace);
            Controls.Add(lblFourthPlace);
            Controls.Add(pictureBox3);
            Controls.Add(pictureBox2);
            Controls.Add(btnBack);
            Controls.Add(pictureBox1);
            Icon = (Icon)resources.GetObject("$this.Icon");
            Name = "BestScores";
            Text = "BestScores";
            ((System.ComponentModel.ISupportInitialize)pictureBox1).EndInit();
            ((System.ComponentModel.ISupportInitialize)pictureBox2).EndInit();
            ((System.ComponentModel.ISupportInitialize)pictureBox3).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button btnBack;
        private PictureBox pictureBox1;
        private PictureBox pictureBox2;
        private PictureBox pictureBox3;
        private Label lblFourthPlace;
        private Label lblFifthPlace;
        private Label lblThirdPlace;
        private Label lblSecondPlace;
        private Label lblFirstPlace;
        private Label label2;
    }
}