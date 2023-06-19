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
            btnLeaveGame = new Button();
            pbUsers = new PictureBox();
            lblUsers = new Label();
            groupBox1 = new GroupBox();
            ((System.ComponentModel.ISupportInitialize)pbUsers).BeginInit();
            groupBox1.SuspendLayout();
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
            lblTimeOut.Location = new Point(6, 98);
            lblTimeOut.Name = "lblTimeOut";
            lblTimeOut.Size = new Size(178, 25);
            lblTimeOut.TabIndex = 51;
            lblTimeOut.Text = "Time per question:";
            // 
            // lblQuestionCount
            // 
            lblQuestionCount.AutoSize = true;
            lblQuestionCount.Font = new Font("Segoe UI", 11F, FontStyle.Bold, GraphicsUnit.Point);
            lblQuestionCount.Location = new Point(6, 30);
            lblQuestionCount.Name = "lblQuestionCount";
            lblQuestionCount.Size = new Size(206, 25);
            lblQuestionCount.TabIndex = 50;
            lblQuestionCount.Text = "Number of questions:";
            // 
            // btnLeaveGame
            // 
            btnLeaveGame.BackColor = Color.CadetBlue;
            btnLeaveGame.Cursor = Cursors.Hand;
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
            // pbUsers
            // 
            pbUsers.BackColor = Color.MintCream;
            pbUsers.Location = new Point(299, 83);
            pbUsers.Name = "pbUsers";
            pbUsers.Size = new Size(433, 200);
            pbUsers.TabIndex = 54;
            pbUsers.TabStop = false;
            // 
            // lblUsers
            // 
            lblUsers.AutoSize = true;
            lblUsers.BackColor = Color.MintCream;
            lblUsers.Font = new Font("Bauhaus 93", 15F, FontStyle.Regular, GraphicsUnit.Point);
            lblUsers.Location = new Point(301, 85);
            lblUsers.Name = "lblUsers";
            lblUsers.Size = new Size(288, 28);
            lblUsers.TabIndex = 53;
            lblUsers.Text = "Current participants are:";
            // 
            // groupBox1
            // 
            groupBox1.Controls.Add(lblQuestionCount);
            groupBox1.Controls.Add(lblTimeOut);
            groupBox1.Font = new Font("Segoe UI", 12F, FontStyle.Italic, GraphicsUnit.Point);
            groupBox1.Location = new Point(43, 85);
            groupBox1.Name = "groupBox1";
            groupBox1.Size = new Size(250, 198);
            groupBox1.TabIndex = 55;
            groupBox1.TabStop = false;
            groupBox1.Text = "Room data:";
            // 
            // RoomMember
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = Color.PaleTurquoise;
            ClientSize = new Size(800, 450);
            Controls.Add(groupBox1);
            Controls.Add(lblRoomName);
            Controls.Add(btnLeaveGame);
            Controls.Add(lblUsers);
            Controls.Add(pbUsers);
            Icon = (Icon)resources.GetObject("$this.Icon");
            Name = "RoomMember";
            Text = "RoomMember";
            FormClosing += RoomMember_FormClosing;
            ((System.ComponentModel.ISupportInitialize)pbUsers).EndInit();
            groupBox1.ResumeLayout(false);
            groupBox1.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label lblRoomName;
        private Label lblTimeOut;
        private Label lblQuestionCount;
        private Button btnLeaveGame;
        private PictureBox pbUsers;
        private Label lblUsers;
        private GroupBox groupBox1;
    }
}