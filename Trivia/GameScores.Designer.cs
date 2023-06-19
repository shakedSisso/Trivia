namespace Trivia
{
    partial class GameScores
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
            components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(GameScores));
            tmrShowResult = new System.Windows.Forms.Timer(components);
            SuspendLayout();
            // 
            // tmrShowResult
            // 
            tmrShowResult.Interval = 5000;
            tmrShowResult.Tick += tmrShowResult_Tick;
            // 
            // GameScores
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = Color.PaleTurquoise;
            ClientSize = new Size(800, 450);
            Icon = (Icon)resources.GetObject("$this.Icon");
            Name = "GameScores";
            Text = "Game scores";
            ResumeLayout(false);
        }

        #endregion

        private System.Windows.Forms.Timer tmrShowResult;
    }
}