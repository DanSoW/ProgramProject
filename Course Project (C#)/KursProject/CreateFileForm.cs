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
    public partial class CreateFileForm : Form
    {
        private OpenFileDialog openFile = null;
        public CreateFileForm()
        {
            InitializeComponent();
            this.FormClosed += this.exitButton_Click;
            openFile = new OpenFileDialog();
            openFile.Title = "Обзор";
            openFile.FileName = "";
            openFile.Filter = "Текстовые файлы (*.txt)|*txt";
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

        private void CreateButton_Click(object sender, EventArgs e)
        {
            nameDirectory.Text = nameDirectory.Text.Trim(' ').Replace(' ', '_');
            nameFile.Text = nameFile.Text.Trim(' ').Replace(' ', '_');

            if((nameDirectory.TextLength <= 0) || (nameFile.TextLength <=0) 
                || (!FileString.CheckNameDirectory(nameDirectory.Text))
                || (!FileString.CheckNameFile(nameFile.Text, ".txt")))
            {
                nameDirectory.Text = "";
                nameFile.Text = "";
                MessageBox.Show("Введены не корректные данные", "Ошибка");
                return;
            }

            openFile.FileName = nameDirectory.Text;

            if (openFile.FileName[openFile.FileName.Length - 1] != '\\')
                openFile.FileName += "\\" + nameFile.Text;
            else
                openFile.FileName += nameFile.Text;

            if (!FileString.SubStrInStr(openFile.FileName, this.extension, openFile.FileName.IndexOf('.')))
                openFile.FileName += this.extension;
            nameDirectory.Text = "";
            nameFile.Text = "";

            this.exitButton_Click(sender, e);
            return;
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
