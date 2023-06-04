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
            gbPlayers = new GroupBox();
            lblMaxNumber = new Label();
            lblQuestionCount = new Label();
            lblTimeOut = new Label();
            lblRoomName = new Label();
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
            // gbPlayers
            // 
            gbPlayers.BackColor = Color.LightCyan;
            gbPlayers.Font = new Font("Bauhaus 93", 13F, FontStyle.Regular, GraphicsUnit.Point);
            gbPlayers.Location = new Point(312, 90);
            gbPlayers.Name = "gbPlayers";
            gbPlayers.Size = new Size(433, 200);
            gbPlayers.TabIndex = 40;
            gbPlayers.TabStop = false;
            gbPlayers.Text = "Current participants are:";
            // 
            // lblMaxNumber
            // 
            lblMaxNumber.AutoSize = true;
            lblMaxNumber.Font = new Font("Segoe UI", 11F, FontStyle.Bold, GraphicsUnit.Point);
            lblMaxNumber.Location = new Point(35, 90);
            lblMaxNumber.Name = "lblMaxNumber";
            lblMaxNumber.Size = new Size(201, 25);
            lblMaxNumber.TabIndex = 41;
            lblMaxNumber.Text = "Max players number:";
            // 
            // lblQuestionCount
            // 
            lblQuestionCount.AutoSize = true;
            lblQuestionCount.Font = new Font("Segoe UI", 11F, FontStyle.Bold, GraphicsUnit.Point);
            lblQuestionCount.Location = new Point(35, 180);
            lblQuestionCount.Name = "lblQuestionCount";
            lblQuestionCount.Size = new Size(206, 25);
            lblQuestionCount.TabIndex = 42;
            lblQuestionCount.Text = "Number of questions:";
            // 
            // lblTimeOut
            // 
            lblTimeOut.AutoSize = true;
            lblTimeOut.Font = new Font("Segoe UI", 11F, FontStyle.Bold, GraphicsUnit.Point);
            lblTimeOut.Location = new Point(35, 265);
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
            // RoomAdmin
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = Color.PaleTurquoise;
            ClientSize = new Size(800, 450);
            Controls.Add(lblRoomName);
            Controls.Add(lblTimeOut);
            Controls.Add(lblQuestionCount);
            Controls.Add(lblMaxNumber);
            Controls.Add(gbPlayers);
            Controls.Add(btnCloseGame);
            Controls.Add(btnStartGame);
            Icon = (Icon)resources.GetObject("$this.Icon");
            Name = "RoomAdmin";
            Text = "RoomAdmin";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button btnCloseGame;
        private Button btnStartGame;
        private GroupBox gbPlayers;
        private Label lblMaxNumber;
        private Label lblQuestionCount;
        private Label lblTimeOut;
        private Label lblRoomName;
    }
}