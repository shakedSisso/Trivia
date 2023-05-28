using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Newtonsoft.Json;

namespace Trivia
{
    public partial class Trivia : Form
    {
        public Trivia()
        {
            InitializeComponent();
        }

        private void btnLogin_Click(object sender, EventArgs e)
        {
            Form fLogin = new Login();
            this.Hide();
            fLogin.ShowDialog();
            this.Dispose();
        }

        private void btnSignup_Click(object sender, EventArgs e)
        {
            Form fSignup = new Signup();
            this.Hide();
            fSignup.ShowDialog();
            this.Dispose();
        }
    }
}
