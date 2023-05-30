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
            this.btnJoinRoom = new System.Windows.Forms.Button();
            this.btnCreateRoom = new System.Windows.Forms.Button();
            this.btnStatus = new System.Windows.Forms.Button();
            this.btnBestScores = new System.Windows.Forms.Button();
            this.btnQuit = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnJoinRoom
            // 
            this.btnJoinRoom.Location = new System.Drawing.Point(10, 19);
            this.btnJoinRoom.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnJoinRoom.Name = "btnJoinRoom";
            this.btnJoinRoom.Size = new System.Drawing.Size(189, 30);
            this.btnJoinRoom.TabIndex = 0;
            this.btnJoinRoom.Text = "Join room";
            this.btnJoinRoom.UseVisualStyleBackColor = true;
            // 
            // btnCreateRoom
            // 
            this.btnCreateRoom.Location = new System.Drawing.Point(10, 53);
            this.btnCreateRoom.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnCreateRoom.Name = "btnCreateRoom";
            this.btnCreateRoom.Size = new System.Drawing.Size(189, 30);
            this.btnCreateRoom.TabIndex = 1;
            this.btnCreateRoom.Text = "Create room";
            this.btnCreateRoom.UseVisualStyleBackColor = true;
            // 
            // btnStatus
            // 
            this.btnStatus.Location = new System.Drawing.Point(10, 88);
            this.btnStatus.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnStatus.Name = "btnStatus";
            this.btnStatus.Size = new System.Drawing.Size(189, 30);
            this.btnStatus.TabIndex = 2;
            this.btnStatus.Text = "My status";
            this.btnStatus.UseVisualStyleBackColor = true;
            // 
            // btnBestScores
            // 
            this.btnBestScores.Location = new System.Drawing.Point(10, 122);
            this.btnBestScores.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnBestScores.Name = "btnBestScores";
            this.btnBestScores.Size = new System.Drawing.Size(189, 30);
            this.btnBestScores.TabIndex = 3;
            this.btnBestScores.Text = "Best Scores";
            this.btnBestScores.UseVisualStyleBackColor = true;
            // 
            // btnQuit
            // 
            this.btnQuit.Location = new System.Drawing.Point(66, 187);
            this.btnQuit.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnQuit.Name = "btnQuit";
            this.btnQuit.Size = new System.Drawing.Size(66, 22);
            this.btnQuit.TabIndex = 4;
            this.btnQuit.Text = "quit";
            this.btnQuit.UseVisualStyleBackColor = true;
            this.btnQuit.Click += new System.EventHandler(this.btnQuit_Click);
            // 
            // Menu
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(210, 218);
            this.Controls.Add(this.btnQuit);
            this.Controls.Add(this.btnBestScores);
            this.Controls.Add(this.btnStatus);
            this.Controls.Add(this.btnCreateRoom);
            this.Controls.Add(this.btnJoinRoom);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "Menu";
            this.Text = "Menu";
            this.ResumeLayout(false);

        }

        #endregion

        private Button btnJoinRoom;
        private Button btnCreateRoom;
        private Button btnStatus;
        private Button btnBestScores;
        private Button btnQuit;
    }
}