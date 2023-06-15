namespace Trivia
{
    partial class Menu
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Menu));
            btnJoinRoom = new Button();
            btnCreateRoom = new Button();
            btnStatus = new Button();
            btnBestScores = new Button();
            btnQuit = new Button();
            lblUsername = new Label();
            lblErrorMessage = new Label();
            SuspendLayout();
            // 
            // btnJoinRoom
            // 
            btnJoinRoom.BackColor = Color.CadetBlue;
            btnJoinRoom.Cursor = Cursors.Hand;
            btnJoinRoom.Font = new Font("Maiandra GD", 15F, FontStyle.Bold, GraphicsUnit.Point);
            btnJoinRoom.ForeColor = SystemColors.ButtonHighlight;
            btnJoinRoom.Location = new Point(40, 177);
            btnJoinRoom.Name = "btnJoinRoom";
            btnJoinRoom.Size = new Size(347, 63);
            btnJoinRoom.TabIndex = 0;
            btnJoinRoom.Text = "Join room";
            btnJoinRoom.UseVisualStyleBackColor = false;
            btnJoinRoom.Click += btnJoinRoom_Click;
            // 
            // btnCreateRoom
            // 
            btnCreateRoom.BackColor = Color.CadetBlue;
            btnCreateRoom.Cursor = Cursors.Hand;
            btnCreateRoom.Font = new Font("Maiandra GD", 15F, FontStyle.Bold, GraphicsUnit.Point);
            btnCreateRoom.ForeColor = SystemColors.ButtonHighlight;
            btnCreateRoom.Location = new Point(40, 262);
            btnCreateRoom.Name = "btnCreateRoom";
            btnCreateRoom.Size = new Size(347, 63);
            btnCreateRoom.TabIndex = 1;
            btnCreateRoom.Text = "Create room";
            btnCreateRoom.UseVisualStyleBackColor = false;
            btnCreateRoom.Click += btnCreateRoom_Click;
            // 
            // btnStatus
            // 
            btnStatus.BackColor = Color.CadetBlue;
            btnStatus.Cursor = Cursors.Hand;
            btnStatus.Font = new Font("Maiandra GD", 15F, FontStyle.Bold, GraphicsUnit.Point);
            btnStatus.ForeColor = SystemColors.ButtonHighlight;
            btnStatus.Location = new Point(419, 177);
            btnStatus.Name = "btnStatus";
            btnStatus.Size = new Size(347, 63);
            btnStatus.TabIndex = 2;
            btnStatus.Text = "My status";
            btnStatus.UseVisualStyleBackColor = false;
            btnStatus.Click += btnStatus_Click;
            // 
            // btnBestScores
            // 
            btnBestScores.BackColor = Color.CadetBlue;
            btnBestScores.Cursor = Cursors.Hand;
            btnBestScores.Font = new Font("Maiandra GD", 15F, FontStyle.Bold, GraphicsUnit.Point);
            btnBestScores.ForeColor = SystemColors.ButtonHighlight;
            btnBestScores.Location = new Point(419, 262);
            btnBestScores.Margin = new Padding(3, 2, 3, 2);
            btnBestScores.Name = "btnBestScores";
            btnBestScores.Size = new Size(347, 63);
            btnBestScores.TabIndex = 3;
            btnBestScores.Text = "Best Scores";
            btnBestScores.UseVisualStyleBackColor = false;
            btnBestScores.Click += btnBestScores_Click;
            // 
            // btnQuit
            // 
            btnQuit.BackColor = Color.CadetBlue;
            btnQuit.Cursor = Cursors.Hand;
            btnQuit.Font = new Font("Maiandra GD", 13F, FontStyle.Regular, GraphicsUnit.Point);
            btnQuit.ForeColor = SystemColors.ButtonHighlight;
            btnQuit.Location = new Point(207, 395);
            btnQuit.Name = "btnQuit";
            btnQuit.Size = new Size(407, 43);
            btnQuit.TabIndex = 4;
            btnQuit.Text = "quit";
            btnQuit.UseVisualStyleBackColor = false;
            btnQuit.Click += btnQuit_Click;
            // 
            // lblUsername
            // 
            lblUsername.AutoSize = true;
            lblUsername.BackColor = Color.PaleTurquoise;
            lblUsername.Font = new Font("Bauhaus 93", 35F, FontStyle.Regular, GraphicsUnit.Point);
            lblUsername.ForeColor = Color.DarkSlateGray;
            lblUsername.Location = new Point(317, 65);
            lblUsername.Name = "lblUsername";
            lblUsername.Size = new Size(166, 67);
            lblUsername.TabIndex = 5;
            lblUsername.Text = "Hello";
            // 
            // lblErrorMessage
            // 
            lblErrorMessage.AutoSize = true;
            lblErrorMessage.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point);
            lblErrorMessage.ForeColor = Color.Maroon;
            lblErrorMessage.Location = new Point(361, 361);
            lblErrorMessage.Name = "lblErrorMessage";
            lblErrorMessage.Size = new Size(0, 20);
            lblErrorMessage.TabIndex = 6;
            // 
            // Menu
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = Color.PaleTurquoise;
            ClientSize = new Size(800, 450);
            Controls.Add(lblErrorMessage);
            Controls.Add(lblUsername);
            Controls.Add(btnQuit);
            Controls.Add(btnBestScores);
            Controls.Add(btnStatus);
            Controls.Add(btnCreateRoom);
            Controls.Add(btnJoinRoom);
            Icon = (Icon)resources.GetObject("$this.Icon");
            Name = "Menu";
            Text = "Menu";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button btnJoinRoom;
        private Button btnCreateRoom;
        private Button btnStatus;
        private Button btnBestScores;
        private Button btnQuit;
        private Label lblUsername;
        private Label lblErrorMessage;
    }
}