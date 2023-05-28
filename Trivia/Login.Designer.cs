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
            btnLogin = new Button();
            lblUsername = new Label();
            label1 = new Label();
            tbUsername = new TextBox();
            tbPassword = new TextBox();
            lblErrorMessage = new Label();
            SuspendLayout();
            // 
            // btnLogin
            // 
            btnLogin.Location = new Point(105, 151);
            btnLogin.Name = "btnLogin";
            btnLogin.Size = new Size(94, 29);
            btnLogin.TabIndex = 0;
            btnLogin.Text = "Log in";
            btnLogin.UseVisualStyleBackColor = true;
            btnLogin.Click += btnLogin_Click;
            // 
            // lblUsername
            // 
            lblUsername.AutoSize = true;
            lblUsername.Location = new Point(53, 47);
            lblUsername.Name = "lblUsername";
            lblUsername.Size = new Size(80, 20);
            lblUsername.TabIndex = 1;
            lblUsername.Text = "username: ";
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(54, 81);
            label1.Name = "label1";
            label1.Size = new Size(79, 20);
            label1.TabIndex = 2;
            label1.Text = "password: ";
            // 
            // tbUsername
            // 
            tbUsername.Location = new Point(140, 44);
            tbUsername.Name = "tbUsername";
            tbUsername.Size = new Size(125, 27);
            tbUsername.TabIndex = 3;
            // 
            // tbPassword
            // 
            tbPassword.Location = new Point(140, 77);
            tbPassword.Name = "tbPassword";
            tbPassword.Size = new Size(125, 27);
            tbPassword.TabIndex = 4;
            tbPassword.UseSystemPasswordChar = true;
            // 
            // lblErrorMessage
            // 
            lblErrorMessage.AutoSize = true;
            lblErrorMessage.ForeColor = Color.Red;
            lblErrorMessage.Location = new Point(122, 122);
            lblErrorMessage.Name = "lblErrorMessage";
            lblErrorMessage.Size = new Size(0, 20);
            lblErrorMessage.TabIndex = 19;
            // 
            // Login
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(306, 202);
            Controls.Add(lblErrorMessage);
            Controls.Add(tbPassword);
            Controls.Add(tbUsername);
            Controls.Add(label1);
            Controls.Add(lblUsername);
            Controls.Add(btnLogin);
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
    }
}