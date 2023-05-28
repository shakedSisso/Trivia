namespace Trivia
{
    partial class Signup
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
            tbPassword = new TextBox();
            tbUsername = new TextBox();
            label1 = new Label();
            lblUsername = new Label();
            btnSignup = new Button();
            lblMail = new Label();
            lblAddress = new Label();
            lblPhoneNumber = new Label();
            lblBirthDate = new Label();
            dtpBirthDate = new DateTimePicker();
            tbMail = new TextBox();
            txAddress = new TextBox();
            tbPhoneNumber = new TextBox();
            lblErrorMessage = new Label();
            SuspendLayout();
            // 
            // tbPassword
            // 
            tbPassword.Location = new Point(151, 67);
            tbPassword.Name = "tbPassword";
            tbPassword.Size = new Size(173, 27);
            tbPassword.TabIndex = 8;
            // 
            // tbUsername
            // 
            tbUsername.Location = new Point(151, 34);
            tbUsername.Name = "tbUsername";
            tbUsername.Size = new Size(173, 27);
            tbUsername.TabIndex = 7;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(66, 74);
            label1.Name = "label1";
            label1.Size = new Size(79, 20);
            label1.TabIndex = 6;
            label1.Text = "password: ";
            // 
            // lblUsername
            // 
            lblUsername.AutoSize = true;
            lblUsername.Location = new Point(65, 41);
            lblUsername.Name = "lblUsername";
            lblUsername.Size = new Size(80, 20);
            lblUsername.TabIndex = 5;
            lblUsername.Text = "username: ";
            // 
            // btnSignup
            // 
            btnSignup.Location = new Point(122, 272);
            btnSignup.Name = "btnSignup";
            btnSignup.Size = new Size(123, 35);
            btnSignup.TabIndex = 9;
            btnSignup.Text = "Sign up";
            btnSignup.UseVisualStyleBackColor = true;
            btnSignup.Click += btnSignup_Click;
            // 
            // lblMail
            // 
            lblMail.AutoSize = true;
            lblMail.Location = new Point(100, 107);
            lblMail.Name = "lblMail";
            lblMail.Size = new Size(45, 20);
            lblMail.TabIndex = 10;
            lblMail.Text = "mail: ";
            // 
            // lblAddress
            // 
            lblAddress.AutoSize = true;
            lblAddress.Location = new Point(78, 140);
            lblAddress.Name = "lblAddress";
            lblAddress.Size = new Size(67, 20);
            lblAddress.TabIndex = 11;
            lblAddress.Text = "address: ";
            // 
            // lblPhoneNumber
            // 
            lblPhoneNumber.AutoSize = true;
            lblPhoneNumber.Location = new Point(32, 173);
            lblPhoneNumber.Name = "lblPhoneNumber";
            lblPhoneNumber.Size = new Size(113, 20);
            lblPhoneNumber.TabIndex = 12;
            lblPhoneNumber.Text = "phone number: ";
            // 
            // lblBirthDate
            // 
            lblBirthDate.AutoSize = true;
            lblBirthDate.Location = new Point(64, 206);
            lblBirthDate.Name = "lblBirthDate";
            lblBirthDate.Size = new Size(81, 20);
            lblBirthDate.TabIndex = 13;
            lblBirthDate.Text = "birth date: ";
            // 
            // dtpBirthDate
            // 
            dtpBirthDate.Format = DateTimePickerFormat.Short;
            dtpBirthDate.Location = new Point(151, 199);
            dtpBirthDate.Name = "dtpBirthDate";
            dtpBirthDate.Size = new Size(173, 27);
            dtpBirthDate.TabIndex = 14;
            // 
            // tbMail
            // 
            tbMail.Location = new Point(151, 100);
            tbMail.Name = "tbMail";
            tbMail.Size = new Size(173, 27);
            tbMail.TabIndex = 15;
            // 
            // txAddress
            // 
            txAddress.Location = new Point(151, 133);
            txAddress.Name = "txAddress";
            txAddress.Size = new Size(173, 27);
            txAddress.TabIndex = 16;
            // 
            // tbPhoneNumber
            // 
            tbPhoneNumber.Location = new Point(151, 166);
            tbPhoneNumber.Name = "tbPhoneNumber";
            tbPhoneNumber.Size = new Size(173, 27);
            tbPhoneNumber.TabIndex = 17;
            // 
            // lblErrorMessage
            // 
            lblErrorMessage.AutoSize = true;
            lblErrorMessage.ForeColor = Color.Red;
            lblErrorMessage.Location = new Point(140, 249);
            lblErrorMessage.Name = "lblErrorMessage";
            lblErrorMessage.Size = new Size(0, 20);
            lblErrorMessage.TabIndex = 18;
            // 
            // Signup
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(373, 333);
            Controls.Add(lblErrorMessage);
            Controls.Add(tbPhoneNumber);
            Controls.Add(txAddress);
            Controls.Add(tbMail);
            Controls.Add(dtpBirthDate);
            Controls.Add(lblBirthDate);
            Controls.Add(lblPhoneNumber);
            Controls.Add(lblAddress);
            Controls.Add(lblMail);
            Controls.Add(btnSignup);
            Controls.Add(tbPassword);
            Controls.Add(tbUsername);
            Controls.Add(label1);
            Controls.Add(lblUsername);
            Name = "Signup";
            Text = "Signup";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private TextBox tbPassword;
        private TextBox tbUsername;
        private Label label1;
        private Label lblUsername;
        private Button btnSignup;
        private Label lblMail;
        private Label lblAddress;
        private Label lblPhoneNumber;
        private Label lblBirthDate;
        private DateTimePicker dtpBirthDate;
        private TextBox tbMail;
        private TextBox txAddress;
        private TextBox tbPhoneNumber;
        private Label lblErrorMessage;
    }
}