namespace Trivia
{
    partial class RoomMember
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(RoomMember));
            lblRoomName = new Label();
            lblTimeOut = new Label();
            lblQuestionCount = new Label();
            gbPlayers = new GroupBox();
            btnLeaveGame = new Button();
            SuspendLayout();
            // 
            // lblRoomName
            // 
            lblRoomName.AutoSize = true;
            lblRoomName.Font = new Font("Bauhaus 93", 25F, FontStyle.Regular, GraphicsUnit.Point);
            lblRoomName.ForeColor = Color.DarkSlateGray;
            lblRoomName.Location = new Point(173, 20);
            lblRoomName.Name = "lblRoomName";
            lblRoomName.Size = new Size(419, 48);
            lblRoomName.TabIndex = 52;
            lblRoomName.Text = "You are connected to";
            // 
            // lblTimeOut
            // 
            lblTimeOut.AutoSize = true;
            lblTimeOut.Font = new Font("Segoe UI", 11F, FontStyle.Bold, GraphicsUnit.Point);
            lblTimeOut.Location = new Point(24, 178);
            lblTimeOut.Name = "lblTimeOut";
            lblTimeOut.Size = new Size(178, 25);
            lblTimeOut.TabIndex = 51;
            lblTimeOut.Text = "Time per question:";
            // 
            // lblQuestionCount
            // 
            lblQuestionCount.AutoSize = true;
            lblQuestionCount.Font = new Font("Segoe UI", 11F, FontStyle.Bold, GraphicsUnit.Point);
            lblQuestionCount.Location = new Point(24, 83);
            lblQuestionCount.Name = "lblQuestionCount";
            lblQuestionCount.Size = new Size(206, 25);
            lblQuestionCount.TabIndex = 50;
            lblQuestionCount.Text = "Number of questions:";
            // 
            // gbPlayers
            // 
            gbPlayers.BackColor = Color.LightCyan;
            gbPlayers.Font = new Font("Bauhaus 93", 13F, FontStyle.Regular, GraphicsUnit.Point);
            gbPlayers.Location = new Point(301, 83);
            gbPlayers.Name = "gbPlayers";
            gbPlayers.Size = new Size(433, 200);
            gbPlayers.TabIndex = 48;
            gbPlayers.TabStop = false;
            gbPlayers.Text = "Current participants are:";
            // 
            // btnLeaveGame
            // 
            btnLeaveGame.BackColor = Color.CadetBlue;
            btnLeaveGame.Font = new Font("Maiandra GD", 15F, FontStyle.Regular, GraphicsUnit.Point);
            btnLeaveGame.ForeColor = SystemColors.ButtonHighlight;
            btnLeaveGame.Location = new Point(221, 329);
            btnLeaveGame.Name = "btnLeaveGame";
            btnLeaveGame.Size = new Size(292, 57);
            btnLeaveGame.TabIndex = 46;
            btnLeaveGame.Text = "Leave game";
            btnLeaveGame.UseVisualStyleBackColor = false;
            btnLeaveGame.Click += btnLeaveGame_Click;
            // 
            // RoomMember
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = Color.PaleTurquoise;
            ClientSize = new Size(800, 450);
            Controls.Add(lblRoomName);
            Controls.Add(lblTimeOut);
            Controls.Add(lblQuestionCount);
            Controls.Add(gbPlayers);
            Controls.Add(btnLeaveGame);
            Icon = (Icon)resources.GetObject("$this.Icon");
            Name = "RoomMember";
            Text = "RoomMember";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label lblRoomName;
        private Label lblTimeOut;
        private Label lblQuestionCount;
        private GroupBox gbPlayers;
        private Button btnLeaveGame;
    }
}