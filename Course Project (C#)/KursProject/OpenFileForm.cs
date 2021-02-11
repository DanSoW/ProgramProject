using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace KursProject
{
    public partial class OpenFileForm : Form
    {
        private OpenFileDialog openFile = null;
        public OpenFileForm()
        {
            InitializeComponent();
            this.FormClosed += exitButton_Click;
            openFile = new OpenFileDialog();
            openFile.Title = "Обзор";
            openFile.FileName = "";
            openFile.Filter = "Текстовые файлы (*.txt)|*.txt";
        }

        private void exitButton_Click(object sender, EventArgs e)
        {
            Form formMainWindow = Application.OpenForms[0];
            formMainWindow.StartPosition = FormStartPosition.Manual;
            formMainWindow.Left = this.Left;
            formMainWindow.Top = this.Top;
            formMainWindow.Show();
            this.Hide();
        }

        private void OpenButton_Click(object sender, EventArgs e)
        {
            openFile.FileName = this.textBox1.Text.Trim(' ');
            if (!FileString.CheckFullNameFile(openFile.FileName, ".txt"))
            {
                MessageBox.Show("Введены не корректные данные", "Ошибка");
                openFile.FileName = "";
                return;
            }
            this.textBox1.Text = "";
            this.exitButton_Click(sender, e);
        }

        private void ViewButton_Click(object sender, EventArgs e)
        {
            if (openFile.ShowDialog() != DialogResult.OK)
            {
                openFile.FileName = "";
                return;
            }

            if (!FileString.CheckFullNameFile(openFile.FileName, ".txt"))
            {
                MessageBox.Show("Введены не корректные данные", "Ошибка");
                openFile.FileName = "";
                return;
            }
            this.exitButton_Click(sender, e);
        }
    }
}
