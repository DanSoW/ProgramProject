using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace KursProject
{
    public partial class ViewStatForm : Form
    {

        private List<UserEntry> userEntries = null; //Все данные содержащиеся в файле
        private string full_name_file; //полное имя файла
        private RequestForm formRequest = null;
        private bool openRequestForm;

        public ViewStatForm()
        {
            InitializeComponent();
            this.FormClosed += ExitButton_Click;
            this.openRequestForm = false;
        }
        public ViewStatForm(string fullNameFile)
        {
            InitializeComponent();
            this.FormClosed += ExitButton_Click;
            EnterInBaseData(fullNameFile);
            this.full_name_file = fullNameFile;
            this.openRequestForm = false;
        }

        private void DefineMaxMinPriceToy(bool c)
        {
            if ((this.userEntries == null) || (this.userEntries.Count <= 0))
                return;
            int index = 0;
            for (int i = 1; i < this.userEntries.Count; i++)
                if (((this.userEntries[index].price_toy > this.userEntries[i].price_toy) && (!c))
                    || ((this.userEntries[index].price_toy < this.userEntries[i].price_toy) && (c)))
                    index = i;
            if (!c)
            {
                this.nameMinPriceToy.Text = this.userEntries[index].name_toy;
                this.minPrice.Text = this.userEntries[index].price_toy.ToString();
            }
            else
            {
                this.nameMaxPriceToy.Text = this.userEntries[index].name_toy;
                this.maxPrice.Text = this.userEntries[index].price_toy.ToString();
            }
        }
        private bool EnterDataInList(string fullNameFile)
        {
            //Запись данных из файла в массив структур userEntries
            if ((!File.Exists(fullNameFile)) || (fullNameFile.Length <= 0))
                return false;
            StreamReader fileReader = new StreamReader(fullNameFile);
            string[] allEntry = fileReader.ReadToEnd().Split('\n'); //Удаление переводов строки
            fileReader.Close();

            this.userEntries = new List<UserEntry>();
            for(int i = 0; i < (allEntry.Length-1); i++)
            {
                string[] entry = allEntry[i].Split(' ');
                entry[1] = entry[1].Replace('_', ' '); //Возврат пробелов
                UserEntry us = new UserEntry();
                us.SetValues(entry[1], System.Convert.ToDouble(entry[2]),
                    System.Convert.ToInt32(entry[3]), System.Convert.ToInt32(entry[4]));
                this.userEntries.Add(us);
            }

            return true;
        }
        private void EnterInBaseData(string fullNameFile)
        {
            //Вставляем в базу данных данные из userEntries соответствующие требованиям задачи
            if (!EnterDataInList(fullNameFile))
                return;
            for (int i = 0; i < this.userEntries.Count; i++)
            {
                this.dataBaseView.Rows.Add(this.userEntries[i].name_toy,
                    (this.userEntries[i].price_toy.ToString() + " руб."), ("от " + this.userEntries[i].valueFrom.ToString() +
                    " до " + this.userEntries[i].valueBefore.ToString()));
                this.dataBaseView.Rows[i].ReadOnly = true;
                this.dataBaseView.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            }

            this.DefineMaxMinPriceToy(false);
            this.DefineMaxMinPriceToy(true);

            return;
        }

        private void ExitButton_Click(object sender, EventArgs e)
        {
            if (this.openRequestForm)
                this.formRequest.Hide();
            Form formMainWindow = Application.OpenForms[0];
            formMainWindow.StartPosition = FormStartPosition.Manual;
            formMainWindow.Left = this.Left;
            formMainWindow.Top = this.Top;
            formMainWindow.Show();
            this.Hide();
        }

        private void dbPrePaint(object sender, DataGridViewRowPrePaintEventArgs e)
        {
            //Нумерация строк таблицы
            int index = e.RowIndex;
            string indexStr = (index + 1).ToString();
            object header = this.dataBaseView.Rows[index].HeaderCell.Value; //Обращение к заголовку строки
            if ((header == null) || (!header.Equals(indexStr)))
                this.dataBaseView.Rows[index].HeaderCell.Value = indexStr; //Присвоение заголовку значения
        }

        private void SetEntryButton_Click(object sender, EventArgs e)
        {
            //Вызываем форму добавления записи
            if (this.openRequestForm)
                this.formRequest.Hide();
            this.Hide();
            ((MainForm)Application.OpenForms[0]).SetData();
        }

        private void InputDataInFile(string fullNameFile)
        {
            if ((this.userEntries == null) || (!File.Exists(fullNameFile)) || (this.userEntries.Count <= 0))
                return;
            StreamWriter fileWriter = new StreamWriter(fullNameFile, false);
            List<UserEntry> buffer = new List<UserEntry>();
            for(int i = 0; i < this.userEntries.Count; i++)
            {
                UserEntry us = new UserEntry();
                us.SetValues(this.userEntries[i].name_toy.Replace(' ', '_'),
                    this.userEntries[i].price_toy,
                    this.userEntries[i].valueFrom,
                    this.userEntries[i].valueBefore);
                buffer.Add(us);
            }
            this.userEntries.Clear();
            this.userEntries = buffer;

            for (int i = 0; i < this.userEntries.Count; i++)
            {
                fileWriter.WriteLine(fullNameFile + " " + this.userEntries[i].name_toy + " " +
                    this.userEntries[i].price_toy.ToString() + " " +
                    this.userEntries[i].valueFrom.ToString() + " " +
                    this.userEntries[i].valueBefore.ToString());
            }
            fileWriter.Close();
            this.userEntries.Clear();
        }
        private void DeleteButton_Click(object sender, EventArgs e)
        {
            if ((this.userEntries == null) || (this.userEntries.Count <= 0) || (this.dataBaseView.CurrentRow.Index < 0))
                return;
            
            this.userEntries.RemoveAt(this.dataBaseView.CurrentRow.Index);
            if ((this.dataBaseView.CurrentRow.Index == 0) && (this.dataBaseView.Rows.Count <= 1))
            {
                this.userEntries.Clear();
                this.dataBaseView.Rows.Clear();
                File.Delete(this.full_name_file);
                File.Create(this.full_name_file).Close();
                ((MainForm)Application.OpenForms[0]).SetAllEntry();
                this.nameMinPriceToy.Text = "";
                this.minPrice.Text = "";
                this.nameMaxPriceToy.Text = "";
                this.maxPrice.Text = "";
                return;
            }
            this.dataBaseView.Rows.Clear();

            this.InputDataInFile(this.full_name_file);
            this.EnterInBaseData(this.full_name_file);
            ((MainForm)Application.OpenForms[0]).SetAllEntry();
        }

        private void ProcButton_Click(object sender, EventArgs e)
        {
            if (this.openRequestForm)
                return;
            formRequest = new RequestForm();
            formRequest.Left = this.Left;
            formRequest.Top = this.Top;
            formRequest.Activate();
            formRequest.Show();
            this.openRequestForm = true;
        }
    }

    public partial class MainForm : Form
    {
        public void SetData()
        {
            this.SetDataButton_Click(null, null);
        }
        public void SetAllEntry()
        {
            this.SetAllCountEntry();
        }
    };
}
