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
        public Trivia(bool firstStart)
        {
            InitializeComponent();
            if (firstStart)
            {
                this.StartPosition = FormStartPosition.CenterScreen;
            }
            else
            {
                this.StartPosition = FormStartPosition.Manual;
                this.Location = LocationManager.GetFormLocation();
            }
        }

        private void btnLogin_Click(object sender, EventArgs e)
        {
            LocationManager.SetFormLocation(this.Location);
            Form fLogin = new Login();
            this.Hide();
            fLogin.ShowDialog();
            this.Dispose();
        }

        private void btnSignup_Click(object sender, EventArgs e)
        {
            LocationManager.SetFormLocation(this.Location);
            Form fSignup = new Signup();
            this.Hide();
            fSignup.ShowDialog();
            this.Dispose();
        }
    }
}
