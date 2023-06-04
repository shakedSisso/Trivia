namespace Trivia
{
    partial class ConnectToRoom
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ConnectToRoom));
            gbRooms = new GroupBox();
            lblNoRooms = new Label();
            btnRefresh = new Button();
            btnJoinRoom = new Button();
            lblUsers = new Label();
            pbUsers = new PictureBox();
            btnBack = new Button();
            gbRooms.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)pbUsers).BeginInit();
            SuspendLayout();
            // 
            // gbRooms
            // 
            gbRooms.BackColor = Color.LightCyan;
            gbRooms.Controls.Add(lblNoRooms);
            gbRooms.Font = new Font("Bauhaus 93", 24F, FontStyle.Regular, GraphicsUnit.Point);
            gbRooms.Location = new Point(48, 30);
            gbRooms.Name = "gbRooms";
            gbRooms.Size = new Size(352, 362);
            gbRooms.TabIndex = 22;
            gbRooms.TabStop = false;
            gbRooms.Text = "Rooms list:";
            // 
            // lblNoRooms
            // 
            lblNoRooms.AutoSize = true;
            lblNoRooms.Font = new Font("Segoe UI", 13F, FontStyle.Bold, GraphicsUnit.Point);
            lblNoRooms.ForeColor = Color.Maroon;
            lblNoRooms.Location = new Point(60, 319);
            lblNoRooms.Name = "lblNoRooms";
            lblNoRooms.Size = new Size(212, 30);
            lblNoRooms.TabIndex = 0;
            lblNoRooms.Text = "No available rooms";
            lblNoRooms.Visible = false;
            // 
            // btnRefresh
            // 
            btnRefresh.BackColor = Color.CadetBlue;
            btnRefresh.Font = new Font("Maiandra GD", 13F, FontStyle.Regular, GraphicsUnit.Point);
            btnRefresh.ForeColor = SystemColors.ButtonHighlight;
            btnRefresh.Location = new Point(512, 58);
            btnRefresh.Name = "btnRefresh";
            btnRefresh.Size = new Size(191, 47);
            btnRefresh.TabIndex = 34;
            btnRefresh.Text = "Refresh";
            btnRefresh.UseVisualStyleBackColor = false;
            btnRefresh.Click += btnRefresh_Click;
            // 
            // btnJoinRoom
            // 
            btnJoinRoom.BackColor = Color.CadetBlue;
            btnJoinRoom.Font = new Font("Maiandra GD", 15F, FontStyle.Regular, GraphicsUnit.Point);
            btnJoinRoom.ForeColor = SystemColors.ButtonHighlight;
            btnJoinRoom.Location = new Point(460, 111);
            btnJoinRoom.Name = "btnJoinRoom";
            btnJoinRoom.Size = new Size(292, 57);
            btnJoinRoom.TabIndex = 33;
            btnJoinRoom.Text = "Join room";
            btnJoinRoom.UseVisualStyleBackColor = false;
            btnJoinRoom.Click += btnJoinRoom_Click;
            // 
            // lblUsers
            // 
            lblUsers.AutoSize = true;
            lblUsers.BackColor = Color.MintCream;
            lblUsers.Font = new Font("Bauhaus 93", 16F, FontStyle.Regular, GraphicsUnit.Point);
            lblUsers.Location = new Point(481, 207);
            lblUsers.Name = "lblUsers";
            lblUsers.Size = new Size(83, 30);
            lblUsers.TabIndex = 36;
            lblUsers.Text = "Users:";
            lblUsers.Visible = false;
            // 
            // pbUsers
            // 
            pbUsers.BackColor = Color.MintCream;
            pbUsers.Location = new Point(479, 204);
            pbUsers.Name = "pbUsers";
            pbUsers.Size = new Size(251, 156);
            pbUsers.TabIndex = 37;
            pbUsers.TabStop = false;
            pbUsers.Visible = false;
            // 
            // btnBack
            // 
            btnBack.BackColor = Color.CadetBlue;
            btnBack.Font = new Font("Maiandra GD", 9F, FontStyle.Bold, GraphicsUnit.Point);
            btnBack.ForeColor = SystemColors.ButtonHighlight;
            btnBack.Location = new Point(640, 409);
            btnBack.Name = "btnBack";
            btnBack.Size = new Size(148, 29);
            btnBack.TabIndex = 23;
            btnBack.Text = "back";
            btnBack.UseVisualStyleBackColor = false;
            btnBack.Click += btnBack_Click;
            // 
            // ConnectToRoom
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = Color.PaleTurquoise;
            ClientSize = new Size(800, 450);
            Controls.Add(btnRefresh);
            Controls.Add(btnBack);
            Controls.Add(btnJoinRoom);
            Controls.Add(gbRooms);
            Controls.Add(lblUsers);
            Controls.Add(pbUsers);
            Icon = (Icon)resources.GetObject("$this.Icon");
            Name = "ConnectToRoom";
            Text = "ConnectToRoom";
            gbRooms.ResumeLayout(false);
            gbRooms.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)pbUsers).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion
        private GroupBox gbRooms;
        private Label lblNoRooms;
        private Button btnBack;
        private Button btnJoinRoom;
        private Button btnRefresh;
        private Label lblUsers;
        private PictureBox pbUsers;
    }
}