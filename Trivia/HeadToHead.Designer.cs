namespace Trivia
{
    partial class HeadToHead
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
            components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(HeadToHead));
            lblWaiting = new Label();
            btnLeaveGame = new Button();
            lblCountDown = new Label();
            label1 = new Label();
            pbLoading = new PictureBox();
            tmrCountDown = new System.Windows.Forms.Timer(components);
            ((System.ComponentModel.ISupportInitialize)pbLoading).BeginInit();
            SuspendLayout();
            // 
            // lblWaiting
            // 
            lblWaiting.AutoSize = true;
            lblWaiting.Font = new Font("Maiandra GD", 23F, FontStyle.Regular, GraphicsUnit.Point);
            lblWaiting.ForeColor = Color.DarkSlateGray;
            lblWaiting.Location = new Point(140, 112);
            lblWaiting.Name = "lblWaiting";
            lblWaiting.Size = new Size(515, 47);
            lblWaiting.TabIndex = 57;
            lblWaiting.Text = "Waiting for another player....";
            // 
            // btnLeaveGame
            // 
            btnLeaveGame.BackColor = Color.CadetBlue;
            btnLeaveGame.Cursor = Cursors.Hand;
            btnLeaveGame.Font = new Font("Maiandra GD", 15F, FontStyle.Regular, GraphicsUnit.Point);
            btnLeaveGame.ForeColor = SystemColors.ButtonHighlight;
            btnLeaveGame.Location = new Point(235, 364);
            btnLeaveGame.Name = "btnLeaveGame";
            btnLeaveGame.Size = new Size(287, 57);
            btnLeaveGame.TabIndex = 56;
            btnLeaveGame.Text = "Leave \"Head to Head\"";
            btnLeaveGame.UseVisualStyleBackColor = false;
            btnLeaveGame.Click += btnLeaveGame_Click;
            // 
            // lblCountDown
            // 
            lblCountDown.AutoSize = true;
            lblCountDown.Font = new Font("Segoe UI", 100F, FontStyle.Bold, GraphicsUnit.Point);
            lblCountDown.ForeColor = Color.DarkSlateGray;
            lblCountDown.Location = new Point(287, 140);
            lblCountDown.Name = "lblCountDown";
            lblCountDown.Size = new Size(189, 221);
            lblCountDown.TabIndex = 52;
            lblCountDown.Text = "0";
            lblCountDown.Visible = false;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Bauhaus 93", 25F, FontStyle.Bold, GraphicsUnit.Point);
            label1.ForeColor = Color.DarkSlateGray;
            label1.Location = new Point(235, 49);
            label1.Name = "label1";
            label1.Size = new Size(287, 48);
            label1.TabIndex = 58;
            label1.Text = "Head to Head";
            // 
            // pbLoading
            // 
            pbLoading.Location = new Point(235, 175);
            pbLoading.Name = "pbLoading";
            pbLoading.Size = new Size(287, 166);
            pbLoading.SizeMode = PictureBoxSizeMode.StretchImage;
            pbLoading.TabIndex = 59;
            pbLoading.TabStop = false;
            // 
            // tmrCountDown
            // 
            tmrCountDown.Interval = 1000;
            tmrCountDown.Tick += tmrCountDown_Tick;
            // 
            // HeadToHead
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = Color.PaleTurquoise;
            ClientSize = new Size(800, 450);
            Controls.Add(label1);
            Controls.Add(lblCountDown);
            Controls.Add(lblWaiting);
            Controls.Add(btnLeaveGame);
            Controls.Add(pbLoading);
            Icon = (Icon)resources.GetObject("$this.Icon");
            Name = "HeadToHead";
            Text = "Head to Head";
            FormClosing += HeadToHead_FormClosing;
            ((System.ComponentModel.ISupportInitialize)pbLoading).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion
        private Label lblWaiting;
        private Button btnLeaveGame;
        private Label lblCountDown;
        private Label label1;
        private PictureBox pbLoading;
        private System.Windows.Forms.Timer tmrCountDown;
    }
}