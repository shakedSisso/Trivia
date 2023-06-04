using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Trivia
{
    public partial class Game : Form
    {
        private string roomName;
        public Game(string name)
        {
            InitializeComponent();
            this.roomName = name;
        }
    }
}
