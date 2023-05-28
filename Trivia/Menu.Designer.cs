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
            btnJoinRoom = new Button();
            btnCreateRoom = new Button();
            btnStatus = new Button();
            btnBestScores = new Button();
            btnQuit = new Button();
            SuspendLayout();
            // 
            // btnJoinRoom
            // 
            btnJoinRoom.Location = new Point(12, 25);
            btnJoinRoom.Name = "btnJoinRoom";
            btnJoinRoom.Size = new Size(216, 40);
            btnJoinRoom.TabIndex = 0;
            btnJoinRoom.Text = "Join room";
            btnJoinRoom.UseVisualStyleBackColor = true;
            btnJoinRoom.Click += btnJoinRoom_Click;
            // 
            // btnCreateRoom
            // 
            btnCreateRoom.Location = new Point(12, 71);
            btnCreateRoom.Name = "btnCreateRoom";
            btnCreateRoom.Size = new Size(216, 40);
            btnCreateRoom.TabIndex = 1;
            btnCreateRoom.Text = "Create room";
            btnCreateRoom.UseVisualStyleBackColor = true;
            btnCreateRoom.Click += btnCreateRoom_Click;
            // 
            // btnStatus
            // 
            btnStatus.Location = new Point(12, 117);
            btnStatus.Name = "btnStatus";
            btnStatus.Size = new Size(216, 40);
            btnStatus.TabIndex = 2;
            btnStatus.Text = "My status";
            btnStatus.UseVisualStyleBackColor = true;
            btnStatus.Click += btnStatus_Click;
            // 
            // btnBestScores
            // 
            btnBestScores.Location = new Point(12, 163);
            btnBestScores.Name = "btnBestScores";
            btnBestScores.Size = new Size(216, 40);
            btnBestScores.TabIndex = 3;
            btnBestScores.Text = "Best Scores";
            btnBestScores.UseVisualStyleBackColor = true;
            btnBestScores.Click += btnBestScores_Click;
            // 
            // btnQuit
            // 
            btnQuit.Location = new Point(76, 249);
            btnQuit.Name = "btnQuit";
            btnQuit.Size = new Size(76, 29);
            btnQuit.TabIndex = 4;
            btnQuit.Text = "quit";
            btnQuit.UseVisualStyleBackColor = true;
            btnQuit.Click += btnQuit_Click;
            // 
            // Menu
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(240, 290);
            Controls.Add(btnQuit);
            Controls.Add(btnBestScores);
            Controls.Add(btnStatus);
            Controls.Add(btnCreateRoom);
            Controls.Add(btnJoinRoom);
            Name = "Menu";
            Text = "Menu";
            ResumeLayout(false);
        }

        #endregion

        private Button btnJoinRoom;
        private Button btnCreateRoom;
        private Button btnStatus;
        private Button btnBestScores;
        private Button btnQuit;
    }
}