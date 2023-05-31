using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Trivia
{
    public partial class Signup : Form
    {
        public Signup()
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.CenterScreen;
        }

        private void btnSignup_Click(object sender, EventArgs e)
        {
            if (tbUsername.Text != string.Empty && tbPassword.Text != string.Empty && tbMail.Text != string.Empty && tbAddress.Text != string.Empty && tbPhoneNumber.Text != string.Empty && dtpBirthDate.Text != string.Empty)
            {
                string username = this.tbUsername.Text;
                string password = this.tbPassword.Text;
                string mail = this.tbMail.Text;
                string address = this.tbAddress.Text;
                string phoneNumber = this.tbPhoneNumber.Text;
                string birthDate = this.dtpBirthDate.Text;
                try
                {
                    Program.GetCommunicator().SignUp(username, password, mail, address, phoneNumber, birthDate);
                    Form fMenu = new Menu(username);
                    this.Hide();
                    fMenu.ShowDialog();
                    this.Dispose();
                }
                catch (Exception ex)
                {
                    ChangeErrorText(ex.Message);
                }
            }
            else
            {
                ChangeErrorText("Please fill all fields");
            }
        }

        private void ChangeErrorText(string message)
        {
            lblErrorMessage.Text = message;
            lblErrorMessage.Left = (this.Width - lblErrorMessage.Width - 20) / 2; //subtracting 20 to include the edge 
        }

        private void btnBack_Click(object sender, EventArgs e)
        {
            Form fTrivia = new Trivia();
            this.Hide();
            fTrivia.ShowDialog();
            this.Dispose();
        }
    }
}
