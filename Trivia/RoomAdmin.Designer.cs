namespace Trivia
{
    partial class RoomAdmin
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(RoomAdmin));
            btnCloseGame = new Button();
            btnStartGame = new Button();
            lblMaxNumber = new Label();
            lblQuestionCount = new Label();
            lblTimeOut = new Label();
            lblRoomName = new Label();
            lblUsers = new Label();
            pbUsers = new PictureBox();
            groupBox1 = new GroupBox();
            ((System.ComponentModel.ISupportInitialize)pbUsers).BeginInit();
            groupBox1.SuspendLayout();
            SuspendLayout();
            // 
            // btnCloseGame
            // 
            btnCloseGame.BackColor = Color.CadetBlue;
            btnCloseGame.Font = new Font("Maiandra GD", 13F, FontStyle.Regular, GraphicsUnit.Point);
            btnCloseGame.ForeColor = SystemColors.ButtonHighlight;
            btnCloseGame.Location = new Point(286, 308);
            btnCloseGame.Name = "btnCloseGame";
            btnCloseGame.Size = new Size(191, 47);
            btnCloseGame.TabIndex = 39;
            btnCloseGame.Text = "Close game";
            btnCloseGame.UseVisualStyleBackColor = false;
            btnCloseGame.Click += btnCloseGame_Click;
            // 
            // btnStartGame
            // 
            btnStartGame.BackColor = Color.CadetBlue;
            btnStartGame.Font = new Font("Maiandra GD", 15F, FontStyle.Regular, GraphicsUnit.Point);
            btnStartGame.ForeColor = SystemColors.ButtonHighlight;
            btnStartGame.Location = new Point(235, 361);
            btnStartGame.Name = "btnStartGame";
            btnStartGame.Size = new Size(292, 57);
            btnStartGame.TabIndex = 38;
            btnStartGame.Text = "Start game";
            btnStartGame.UseVisualStyleBackColor = false;
            btnStartGame.Click += btnStartGame_Click;
            // 
            // lblMaxNumber
            // 
            lblMaxNumber.AutoSize = true;
            lblMaxNumber.Font = new Font("Segoe UI", 11F, FontStyle.Bold, GraphicsUnit.Point);
            lblMaxNumber.Location = new Point(6, 30);
            lblMaxNumber.Name = "lblMaxNumber";
            lblMaxNumber.Size = new Size(201, 25);
            lblMaxNumber.TabIndex = 41;
            lblMaxNumber.Text = "Max players number:";
            // 
            // lblQuestionCount
            // 
            lblQuestionCount.AutoSize = true;
            lblQuestionCount.Font = new Font("Segoe UI", 11F, FontStyle.Bold, GraphicsUnit.Point);
            lblQuestionCount.Location = new Point(6, 87);
            lblQuestionCount.Name = "lblQuestionCount";
            lblQuestionCount.Size = new Size(206, 25);
            lblQuestionCount.TabIndex = 42;
            lblQuestionCount.Text = "Number of questions:";
            // 
            // lblTimeOut
            // 
            lblTimeOut.AutoSize = true;
            lblTimeOut.Font = new Font("Segoe UI", 11F, FontStyle.Bold, GraphicsUnit.Point);
            lblTimeOut.Location = new Point(6, 150);
            lblTimeOut.Name = "lblTimeOut";
            lblTimeOut.Size = new Size(178, 25);
            lblTimeOut.TabIndex = 43;
            lblTimeOut.Text = "Time per question:";
            // 
            // lblRoomName
            // 
            lblRoomName.AutoSize = true;
            lblRoomName.Font = new Font("Bauhaus 93", 25F, FontStyle.Regular, GraphicsUnit.Point);
            lblRoomName.ForeColor = Color.DarkSlateGray;
            lblRoomName.Location = new Point(184, 27);
            lblRoomName.Name = "lblRoomName";
            lblRoomName.Size = new Size(419, 48);
            lblRoomName.TabIndex = 44;
            lblRoomName.Text = "You are connected to";
            // 
            // lblUsers
            // 
            lblUsers.AutoSize = true;
            lblUsers.BackColor = Color.MintCream;
            lblUsers.Font = new Font("Bauhaus 93", 15F, FontStyle.Regular, GraphicsUnit.Point);
            lblUsers.Location = new Point(307, 92);
            lblUsers.Name = "lblUsers";
            lblUsers.Size = new Size(288, 28);
            lblUsers.TabIndex = 55;
            lblUsers.Text = "Current participants are:";
            // 
            // pbUsers
            // 
            pbUsers.BackColor = Color.MintCream;
            pbUsers.Location = new Point(305, 90);
            pbUsers.Name = "pbUsers";
            pbUsers.Size = new Size(433, 200);
            pbUsers.TabIndex = 56;
            pbUsers.TabStop = false;
            // 
            // groupBox1
            // 
            groupBox1.Controls.Add(lblMaxNumber);
            groupBox1.Controls.Add(lblQuestionCount);
            groupBox1.Controls.Add(lblTimeOut);
            groupBox1.Font = new Font("Segoe UI", 12F, FontStyle.Italic, GraphicsUnit.Point);
            groupBox1.Location = new Point(49, 92);
            groupBox1.Name = "groupBox1";
            groupBox1.Size = new Size(250, 198);
            groupBox1.TabIndex = 57;
            groupBox1.TabStop = false;
            groupBox1.Text = "Room data:";
            // 
            // RoomAdmin
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = Color.PaleTurquoise;
            ClientSize = new Size(800, 450);
            Controls.Add(groupBox1);
            Controls.Add(lblRoomName);
            Controls.Add(btnCloseGame);
            Controls.Add(btnStartGame);
            Controls.Add(lblUsers);
            Controls.Add(pbUsers);
            Icon = (Icon)resources.GetObject("$this.Icon");
            Name = "RoomAdmin";
            Text = "RoomAdmin";
            FormClosing += RoomAdmin_FormClosing;
            ((System.ComponentModel.ISupportInitialize)pbUsers).EndInit();
            groupBox1.ResumeLayout(false);
            groupBox1.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button btnCloseGame;
        private Button btnStartGame;
        private Label lblMaxNumber;
        private Label lblQuestionCount;
        private Label lblTimeOut;
        private Label lblRoomName;
        private Label lblUsers;
        private PictureBox pbUsers;
        private GroupBox groupBox1;
    }
}