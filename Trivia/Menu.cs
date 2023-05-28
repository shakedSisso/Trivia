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
    public partial class Menu : Form
    {
        public Menu()
        {
            InitializeComponent();
        }

        private void btnQuit_Click(object sender, EventArgs e)
        {
            //logout
            Application.Exit();
        }

        private void btnJoinRoom_Click(object sender, EventArgs e)
        {
            Form fMember = new RoomMember();
            this.Hide();
            fMember.ShowDialog();
            this.Show();
        }

        private void btnCreateRoom_Click(object sender, EventArgs e)
        {
            Form fAdmin = new RoomAdmin();
            this.Hide();
            fAdmin.ShowDialog();
            this.Show();
        }

        private void btnStatus_Click(object sender, EventArgs e)
        { 
            Form fStatus = new Menu();
            this.Hide();
            fStatus.ShowDialog();
            this.Show();
        }

        private void btnBestScores_Click(object sender, EventArgs e)
        {
            Form fBestScores = new Menu();
            this.Hide();
            fBestScores.ShowDialog();
            this.Show();
        }
    }
}
