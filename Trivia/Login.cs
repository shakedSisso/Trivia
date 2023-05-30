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
    public partial class Login : Form
    {
        public Login()
        {
            InitializeComponent();
        }

        private void btnLogin_Click(object sender, EventArgs e)
        {
            string username = this.tbUsername.Text;
            string password = this.tbPassword.Text;
            try
            {
                Program.GetCommunicator().Login(username, password);
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
