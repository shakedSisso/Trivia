namespace Trivia
{
    partial class CreateRoom
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CreateRoom));
            btnBack = new Button();
            pictureBox1 = new PictureBox();
            tbTimeForQuestions = new TextBox();
            tbNumOfQuestions = new TextBox();
            tbNumOfPlayers = new TextBox();
            label2 = new Label();
            label4 = new Label();
            label3 = new Label();
            tbRoomName = new TextBox();
            label1 = new Label();
            btnCreateRoom = new Button();
            label5 = new Label();
            lblErrorMessage = new Label();
            ((System.ComponentModel.ISupportInitialize)pictureBox1).BeginInit();
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
            btnBack.TabIndex = 22;
            btnBack.Text = "back";
            btnBack.UseVisualStyleBackColor = false;
            btnBack.Click += btnBack_Click_1;
            // 
            // pictureBox1
            // 
            pictureBox1.BackColor = Color.LightCyan;
            pictureBox1.Location = new Point(106, 27);
            pictureBox1.Name = "pictureBox1";
            pictureBox1.Size = new Size(593, 294);
            pictureBox1.TabIndex = 23;
            pictureBox1.TabStop = false;
            // 
            // tbTimeForQuestions
            // 
            tbTimeForQuestions.BackColor = SystemColors.ButtonHighlight;
            tbTimeForQuestions.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point);
            tbTimeForQuestions.Location = new Point(387, 253);
            tbTimeForQuestions.Name = "tbTimeForQuestions";
            tbTimeForQuestions.Size = new Size(265, 34);
            tbTimeForQuestions.TabIndex = 31;
            tbTimeForQuestions.Text = "4";
            // 
            // tbNumOfQuestions
            // 
            tbNumOfQuestions.BackColor = SystemColors.ButtonHighlight;
            tbNumOfQuestions.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point);
            tbNumOfQuestions.Location = new Point(387, 192);
            tbNumOfQuestions.Name = "tbNumOfQuestions";
            tbNumOfQuestions.Size = new Size(265, 34);
            tbNumOfQuestions.TabIndex = 30;
            tbNumOfQuestions.Text = "5";
            // 
            // tbNumOfPlayers
            // 
            tbNumOfPlayers.BackColor = SystemColors.ButtonHighlight;
            tbNumOfPlayers.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point);
            tbNumOfPlayers.Location = new Point(387, 125);
            tbNumOfPlayers.Name = "tbNumOfPlayers";
            tbNumOfPlayers.Size = new Size(265, 34);
            tbNumOfPlayers.TabIndex = 29;
            tbNumOfPlayers.Text = "3";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.BackColor = Color.LightCyan;
            label2.Font = new Font("Segoe UI", 13F, FontStyle.Italic, GraphicsUnit.Point);
            label2.Location = new Point(139, 129);
            label2.Name = "label2";
            label2.Size = new Size(202, 30);
            label2.TabIndex = 28;
            label2.Text = "Number of players: ";
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.BackColor = Color.LightCyan;
            label4.Font = new Font("Segoe UI", 13F, FontStyle.Italic, GraphicsUnit.Point);
            label4.Location = new Point(139, 255);
            label4.Name = "label4";
            label4.Size = new Size(185, 30);
            label4.TabIndex = 27;
            label4.Text = "Time for question:";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.BackColor = Color.LightCyan;
            label3.Font = new Font("Segoe UI", 13F, FontStyle.Italic, GraphicsUnit.Point);
            label3.Location = new Point(139, 194);
            label3.Name = "label3";
            label3.Size = new Size(217, 30);
            label3.TabIndex = 26;
            label3.Text = "Number of questions:";
            // 
            // tbRoomName
            // 
            tbRoomName.BackColor = SystemColors.ButtonHighlight;
            tbRoomName.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point);
            tbRoomName.Location = new Point(387, 62);
            tbRoomName.Name = "tbRoomName";
            tbRoomName.Size = new Size(265, 34);
            tbRoomName.TabIndex = 25;
            tbRoomName.Text = "room_name";
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.BackColor = Color.LightCyan;
            label1.Font = new Font("Segoe UI", 13F, FontStyle.Italic, GraphicsUnit.Point);
            label1.Location = new Point(139, 64);
            label1.Name = "label1";
            label1.Size = new Size(134, 30);
            label1.TabIndex = 24;
            label1.Text = "Room name:";
            // 
            // btnCreateRoom
            // 
            btnCreateRoom.BackColor = Color.CadetBlue;
            btnCreateRoom.Font = new Font("Maiandra GD", 15F, FontStyle.Regular, GraphicsUnit.Point);
            btnCreateRoom.ForeColor = SystemColors.ButtonHighlight;
            btnCreateRoom.Location = new Point(250, 369);
            btnCreateRoom.Name = "btnCreateRoom";
            btnCreateRoom.Size = new Size(292, 57);
            btnCreateRoom.TabIndex = 32;
            btnCreateRoom.Text = "Create room";
            btnCreateRoom.UseVisualStyleBackColor = false;
            btnCreateRoom.Click += btnCreateRoom_Click;
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Location = new Point(362, 336);
            label5.Name = "label5";
            label5.Size = new Size(0, 20);
            label5.TabIndex = 33;
            // 
            // lblErrorMessage
            // 
            lblErrorMessage.AutoSize = true;
            lblErrorMessage.Font = new Font("Segoe UI", 9F, FontStyle.Bold, GraphicsUnit.Point);
            lblErrorMessage.ForeColor = Color.Maroon;
            lblErrorMessage.Location = new Point(385, 340);
            lblErrorMessage.Name = "lblErrorMessage";
            lblErrorMessage.Size = new Size(0, 20);
            lblErrorMessage.TabIndex = 34;
            // 
            // CreateRoom
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = Color.PaleTurquoise;
            ClientSize = new Size(800, 450);
            Controls.Add(lblErrorMessage);
            Controls.Add(label5);
            Controls.Add(btnCreateRoom);
            Controls.Add(tbTimeForQuestions);
            Controls.Add(tbNumOfQuestions);
            Controls.Add(tbNumOfPlayers);
            Controls.Add(label2);
            Controls.Add(label4);
            Controls.Add(label3);
            Controls.Add(tbRoomName);
            Controls.Add(label1);
            Controls.Add(pictureBox1);
            Controls.Add(btnBack);
            Icon = (Icon)resources.GetObject("$this.Icon");
            Name = "CreateRoom";
            Text = "Create room";
            ((System.ComponentModel.ISupportInitialize)pictureBox1).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button btnBack;
        private PictureBox pictureBox1;
        private TextBox tbTimeForQuestions;
        private TextBox tbNumOfQuestions;
        private TextBox tbNumOfPlayers;
        private Label label2;
        private Label label4;
        private Label label3;
        private TextBox tbRoomName;
        private Label label1;
        private Button btnCreateRoom;
        private Label label5;
        private Label lblErrorMessage;
    }
}