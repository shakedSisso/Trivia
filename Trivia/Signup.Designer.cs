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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Signup));
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
            tbAddress = new TextBox();
            tbPhoneNumber = new TextBox();
            lblErrorMessage = new Label();
            btnBack = new Button();
            label2 = new Label();
            SuspendLayout();
            // 
            // tbPassword
            // 
            tbPassword.BackColor = SystemColors.ButtonHighlight;
            tbPassword.Location = new Point(400, 138);
            tbPassword.Name = "tbPassword";
            tbPassword.Size = new Size(265, 27);
            tbPassword.TabIndex = 8;
            // 
            // tbUsername
            // 
            tbUsername.BackColor = SystemColors.ButtonHighlight;
            tbUsername.Location = new Point(400, 104);
            tbUsername.Name = "tbUsername";
            tbUsername.Size = new Size(265, 27);
            tbUsername.TabIndex = 7;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Segoe UI", 13F, FontStyle.Italic, GraphicsUnit.Point);
            label1.Location = new Point(166, 133);
            label1.Name = "label1";
            label1.Size = new Size(114, 30);
            label1.TabIndex = 6;
            label1.Text = "password: ";
            // 
            // lblUsername
            // 
            lblUsername.AutoSize = true;
            lblUsername.Font = new Font("Segoe UI", 13F, FontStyle.Italic, GraphicsUnit.Point);
            lblUsername.Location = new Point(166, 99);
            lblUsername.Name = "lblUsername";
            lblUsername.Size = new Size(118, 30);
            lblUsername.TabIndex = 5;
            lblUsername.Text = "username: ";
            // 
            // btnSignup
            // 
            btnSignup.BackColor = Color.CadetBlue;
            btnSignup.Cursor = Cursors.Hand;
            btnSignup.Font = new Font("Maiandra GD", 15F, FontStyle.Regular, GraphicsUnit.Point);
            btnSignup.ForeColor = SystemColors.ButtonHighlight;
            btnSignup.Location = new Point(236, 347);
            btnSignup.Name = "btnSignup";
            btnSignup.Size = new Size(292, 57);
            btnSignup.TabIndex = 9;
            btnSignup.Text = "Sign up";
            btnSignup.UseVisualStyleBackColor = false;
            btnSignup.Click += btnSignup_Click;
            // 
            // lblMail
            // 
            lblMail.AutoSize = true;
            lblMail.Font = new Font("Segoe UI", 13F, FontStyle.Italic, GraphicsUnit.Point);
            lblMail.Location = new Point(166, 167);
            lblMail.Name = "lblMail";
            lblMail.Size = new Size(67, 30);
            lblMail.TabIndex = 10;
            lblMail.Text = "mail: ";
            // 
            // lblAddress
            // 
            lblAddress.AutoSize = true;
            lblAddress.Font = new Font("Segoe UI", 13F, FontStyle.Italic, GraphicsUnit.Point);
            lblAddress.Location = new Point(166, 198);
            lblAddress.Name = "lblAddress";
            lblAddress.Size = new Size(97, 30);
            lblAddress.TabIndex = 11;
            lblAddress.Text = "address: ";
            // 
            // lblPhoneNumber
            // 
            lblPhoneNumber.AutoSize = true;
            lblPhoneNumber.Font = new Font("Segoe UI", 13F, FontStyle.Italic, GraphicsUnit.Point);
            lblPhoneNumber.Location = new Point(166, 231);
            lblPhoneNumber.Name = "lblPhoneNumber";
            lblPhoneNumber.Size = new Size(163, 30);
            lblPhoneNumber.TabIndex = 12;
            lblPhoneNumber.Text = "phone number: ";
            // 
            // lblBirthDate
            // 
            lblBirthDate.AutoSize = true;
            lblBirthDate.Font = new Font("Segoe UI", 13F, FontStyle.Italic, GraphicsUnit.Point);
            lblBirthDate.Location = new Point(166, 266);
            lblBirthDate.Name = "lblBirthDate";
            lblBirthDate.Size = new Size(117, 30);
            lblBirthDate.TabIndex = 13;
            lblBirthDate.Text = "birth date: ";
            // 
            // dtpBirthDate
            // 
            dtpBirthDate.CalendarForeColor = SystemColors.ActiveCaptionText;
            dtpBirthDate.CalendarMonthBackground = Color.LightCyan;
            dtpBirthDate.CalendarTitleBackColor = Color.LightCyan;
            dtpBirthDate.Format = DateTimePickerFormat.Short;
            dtpBirthDate.Location = new Point(400, 269);
            dtpBirthDate.Name = "dtpBirthDate";
            dtpBirthDate.Size = new Size(265, 27);
            dtpBirthDate.TabIndex = 14;
            // 
            // tbMail
            // 
            tbMail.BackColor = SystemColors.ButtonHighlight;
            tbMail.Location = new Point(400, 170);
            tbMail.Name = "tbMail";
            tbMail.Size = new Size(265, 27);
            tbMail.TabIndex = 15;
            // 
            // tbAddress
            // 
            tbAddress.BackColor = SystemColors.ButtonHighlight;
            tbAddress.Location = new Point(400, 203);
            tbAddress.Name = "tbAddress";
            tbAddress.Size = new Size(265, 27);
            tbAddress.TabIndex = 16;
            // 
            // tbPhoneNumber
            // 
            tbPhoneNumber.BackColor = SystemColors.ButtonHighlight;
            tbPhoneNumber.Location = new Point(400, 236);
            tbPhoneNumber.Name = "tbPhoneNumber";
            tbPhoneNumber.Size = new Size(265, 27);
            tbPhoneNumber.TabIndex = 17;
            // 
            // lblErrorMessage
            // 
            lblErrorMessage.AutoSize = true;
            lblErrorMessage.Font = new Font("Segoe UI", 13F, FontStyle.Regular, GraphicsUnit.Point);
            lblErrorMessage.ForeColor = Color.Maroon;
            lblErrorMessage.Location = new Point(271, 307);
            lblErrorMessage.Name = "lblErrorMessage";
            lblErrorMessage.Size = new Size(0, 30);
            lblErrorMessage.TabIndex = 18;
            // 
            // btnBack
            // 
            btnBack.BackColor = Color.CadetBlue;
            btnBack.Cursor = Cursors.Hand;
            btnBack.Font = new Font("Maiandra GD", 9F, FontStyle.Bold, GraphicsUnit.Point);
            btnBack.ForeColor = SystemColors.ButtonHighlight;
            btnBack.Location = new Point(640, 409);
            btnBack.Name = "btnBack";
            btnBack.Size = new Size(148, 29);
            btnBack.TabIndex = 21;
            btnBack.Text = "back";
            btnBack.UseVisualStyleBackColor = false;
            btnBack.Click += btnBack_Click;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Font = new Font("Bauhaus 93", 25F, FontStyle.Regular, GraphicsUnit.Point);
            label2.ForeColor = Color.DarkSlateGray;
            label2.Location = new Point(254, 33);
            label2.Name = "label2";
            label2.Size = new Size(261, 48);
            label2.TabIndex = 22;
            label2.Text = "Sign up page";
            // 
            // Signup
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = Color.PaleTurquoise;
            ClientSize = new Size(800, 450);
            Controls.Add(label2);
            Controls.Add(btnBack);
            Controls.Add(lblErrorMessage);
            Controls.Add(tbPhoneNumber);
            Controls.Add(tbAddress);
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
            Icon = (Icon)resources.GetObject("$this.Icon");
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
        private TextBox tbAddress;
        private TextBox tbPhoneNumber;
        private Label lblErrorMessage;
        private Button btnBack;
        private Label label2;
    }
}