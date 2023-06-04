using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace Trivia
{
    public partial class Login : Form
    {
        public Login(Point startLocation)
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.Manual;
            this.Location = startLocation;
        }

        private void btnLogin_Click(object sender, EventArgs e)
        {
            if (tbUsername.Text != string.Empty && tbPassword.Text != string.Empty)
            {
                string username = tbUsername.Text;
                string password = tbPassword.Text;
                try
                {
                    Program.GetCommunicator().Login(username, password);
                    Form fMenu = new Menu(this.Location, username);
                    this.Hide();
                    fMenu.ShowDialog();
                    this.Dispose();
                }
                catch (Exception ex)
                {
                    ChangeErrorText(ex.Message);
                    tbUsername.Text = string.Empty;
                    tbPassword.Text = string.Empty;
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
            Form fTrivia = new Trivia(this.Location);
            this.Hide();
            fTrivia.ShowDialog();
            this.Dispose();
        }
    }
}
