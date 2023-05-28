namespace Trivia
{
    partial class Trivia
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
            btnSignup = new Button();
            SuspendLayout();
            // 
            // btnLogin
            // 
            btnLogin.Location = new Point(40, 43);
            btnLogin.Name = "btnLogin";
            btnLogin.Size = new Size(204, 44);
            btnLogin.TabIndex = 0;
            btnLogin.Text = "Log in";
            btnLogin.UseVisualStyleBackColor = true;
            btnLogin.Click += btnLogin_Click;
            // 
            // btnSignup
            // 
            btnSignup.Location = new Point(40, 93);
            btnSignup.Name = "btnSignup";
            btnSignup.Size = new Size(204, 44);
            btnSignup.TabIndex = 1;
            btnSignup.Text = "Sign up";
            btnSignup.UseVisualStyleBackColor = true;
            btnSignup.Click += btnSignup_Click;
            // 
            // Trivia
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = Color.Silver;
            ClientSize = new Size(271, 175);
            Controls.Add(btnSignup);
            Controls.Add(btnLogin);
            Name = "Trivia";
            Text = "Trivia";
            ResumeLayout(false);
        }

        #endregion

        private Button btnLogin;
        private Button btnSignup;
    }
}