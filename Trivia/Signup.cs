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
        }

        private void btnSignup_Click(object sender, EventArgs e)
        {
            string username = this.tbUsername.Text;
            string password = this.tbPassword.Text;
            string mail = this.tbMail.Text;
            string address = this.txAddress.Text;
            string phoneNumber = this.tbPhoneNumber.Text;
            string birthDate = this.dtpBirthDate.Text;
            try
            {
                Program.GetCommunicator().SignUp(username, password, mail, address, phoneNumber, birthDate);
            }
            catch (Exception ex)
            {
                return;
            }
            Form fMenu = new Menu();
            this.Hide();
            fMenu.ShowDialog();
            this.Dispose();
        }

    }
}
