namespace Trivia
{
    partial class Login
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Login));
            btnLogin = new Button();
            lblUsername = new Label();
            label1 = new Label();
            tbUsername = new TextBox();
            tbPassword = new TextBox();
            lblErrorMessage = new Label();
            btnBack = new Button();
            label2 = new Label();
            SuspendLayout();
            // 
            // btnLogin
            // 
            btnLogin.BackColor = Color.CadetBlue;
            btnLogin.Font = new Font("Maiandra GD", 15F, FontStyle.Bold, GraphicsUnit.Point);
            btnLogin.ForeColor = SystemColors.ButtonHighlight;
            btnLogin.Location = new Point(254, 330);
            btnLogin.Name = "btnLogin";
            btnLogin.RightToLeft = RightToLeft.Yes;
            btnLogin.Size = new Size(292, 57);
            btnLogin.TabIndex = 0;
            btnLogin.Text = "Log in";
            btnLogin.UseVisualStyleBackColor = false;
            btnLogin.Click += btnLogin_Click;
            // 
            // lblUsername
            // 
            lblUsername.AutoSize = true;
            lblUsername.Font = new Font("Segoe UI", 13F, FontStyle.Italic, GraphicsUnit.Point);
            lblUsername.Location = new Point(192, 157);
            lblUsername.Name = "lblUsername";
            lblUsername.Size = new Size(118, 30);
            lblUsername.TabIndex = 1;
            lblUsername.Text = "username: ";
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Segoe UI", 13F, FontStyle.Italic, GraphicsUnit.Point);
            label1.Location = new Point(196, 222);
            label1.Name = "label1";
            label1.Size = new Size(114, 30);
            label1.TabIndex = 2;
            label1.Text = "password: ";
            // 
            // tbUsername
            // 
            tbUsername.BackColor = SystemColors.ButtonHighlight;
            tbUsername.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point);
            tbUsername.Location = new Point(363, 155);
            tbUsername.Name = "tbUsername";
            tbUsername.Size = new Size(265, 34);
            tbUsername.TabIndex = 3;
            // 
            // tbPassword
            // 
            tbPassword.BackColor = SystemColors.ButtonHighlight;
            tbPassword.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point);
            tbPassword.Location = new Point(363, 220);
            tbPassword.Name = "tbPassword";
            tbPassword.Size = new Size(265, 34);
            tbPassword.TabIndex = 4;
            tbPassword.UseSystemPasswordChar = true;
            // 
            // lblErrorMessage
            // 
            lblErrorMessage.AutoSize = true;
            lblErrorMessage.Font = new Font("Segoe UI", 13F, FontStyle.Bold, GraphicsUnit.Point);
            lblErrorMessage.ForeColor = Color.Maroon;
            lblErrorMessage.Location = new Point(287, 288);
            lblErrorMessage.Name = "lblErrorMessage";
            lblErrorMessage.Size = new Size(0, 30);
            lblErrorMessage.TabIndex = 19;
            // 
            // btnBack
            // 
            btnBack.BackColor = Color.CadetBlue;
            btnBack.Font = new Font("Maiandra GD", 9F, FontStyle.Bold, GraphicsUnit.Point);
            btnBack.ForeColor = SystemColors.ButtonHighlight;
            btnBack.Location = new Point(640, 409);
            btnBack.Name = "btnBack";
            btnBack.Size = new Size(148, 29);
            btnBack.TabIndex = 20;
            btnBack.Text = "back";
            btnBack.UseVisualStyleBackColor = false;
            btnBack.Click += btnBack_Click;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Font = new Font("Bauhaus 93", 25F, FontStyle.Regular, GraphicsUnit.Point);
            label2.ForeColor = Color.DarkSlateGray;
            label2.Location = new Point(267, 54);
            label2.Name = "label2";
            label2.Size = new Size(234, 48);
            label2.TabIndex = 21;
            label2.Text = "Log in page";
            // 
            // Login
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = Color.PaleTurquoise;
            ClientSize = new Size(800, 450);
            Controls.Add(label2);
            Controls.Add(btnBack);
            Controls.Add(lblErrorMessage);
            Controls.Add(tbPassword);
            Controls.Add(tbUsername);
            Controls.Add(label1);
            Controls.Add(lblUsername);
            Controls.Add(btnLogin);
            Icon = (Icon)resources.GetObject("$this.Icon");
            Name = "Login";
            Text = "Login";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button btnLogin;
        private Label lblUsername;
        private Label label1;
        private TextBox tbUsername;
        private TextBox tbPassword;
        private Label lblErrorMessage;
        private Button btnBack;
        private Label label2;
    }
}