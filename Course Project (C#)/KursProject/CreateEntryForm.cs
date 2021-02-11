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
    public struct UserEntry
    {
        public string name_toy;
        public double price_toy;
        public int valueFrom;
        public int valueBefore;
        public bool CheckAllAttribute()
        {
            if ((name_toy.Length <= 0) || (price_toy <= 0.0)
                || (valueFrom <= 0) || (valueBefore <= 0))
                return false;
            bool f = false;
            for (int i = 0; (i < name_toy.Length) && (!f); i++)
                if (((name_toy[i] >= 'a') && (name_toy[i] <= 'z'))
                    || ((name_toy[i] >= 'A') && (name_toy[i] <= 'Z'))
                    || ((name_toy[i] >= '1') && (name_toy[i] <= '9'))
                    || ((name_toy[i] >= 'А') && (name_toy[i] <= 'п'))
                    || ((name_toy[i] >= 'р') && (name_toy[i] <= 'я')))
                    f = true;
            return f;
        }
        public void SetStandartValues()
        {
            name_toy = "";
            price_toy = 0;
            valueFrom = valueBefore = 0;
        }
        public void SetValues(string ntoy, double ptoy, int vFrom, int vBefore)
        {
            name_toy = ntoy;
            price_toy = ptoy;
            valueFrom = vFrom;
            valueBefore = vBefore;
        }
    }

    public partial class CreateEntryForm : Form
    {
        public CreateEntryForm()
        {
            InitializeComponent();
            this.FormClosed += this.ExitButton_Click;
            dynamicEntry.SetStandartValues();
            this.priceToyBox.MaxLength = 10;
            this.valueFromBox.MaxLength = 2;
            this.valueBeforeBox.MaxLength = 2;
        }

        private void ExitButton_Click(object sender, EventArgs e)
        {
            Form formMainWindow = Application.OpenForms[0];
            formMainWindow.StartPosition = FormStartPosition.Manual;
            formMainWindow.Left = this.Left;
            formMainWindow.Top = this.Top;
            formMainWindow.Show();
            this.Hide();
        }

        private void AddEntryButton_Click(object sender, EventArgs e)
        {
            dynamicEntry.SetStandartValues();
            
            this.nameToyBox.Text = this.nameToyBox.Text.Trim(' ');
            if ((this.nameToyBox.Text.Length <= 0) || (this.priceToyBox.Text.Length <= 0)
                || (this.valueFromBox.Text.Length <= 0) || (this.valueBeforeBox.Text.Length <= 0))
            {
                MessageBox.Show("Необходимо заполнить все поля ввода!", "Ошибка");
                return;
            }

            this.nameToyBox.Text = this.nameToyBox.Text.Replace(' ', '_');
            dynamicEntry.SetValues(this.nameToyBox.Text, System.Convert.ToDouble(this.priceToyBox.Text),
                System.Convert.ToInt32(this.valueFromBox.Text), System.Convert.ToInt32(this.valueBeforeBox.Text));
           
            if((dynamicEntry.valueFrom > dynamicEntry.valueBefore) || (!dynamicEntry.CheckAllAttribute()))
            {
                dynamicEntry.SetStandartValues();
                MessageBox.Show("Введены не корректные данные!", "Ошибка");
            }

            this.nameToyBox.Text = "";
            this.priceToyBox.Text = "";
            this.valueFromBox.Text = "";
            this.valueBeforeBox.Text = "";
            this.flagPoint_Press = false;
        }

        private bool flagPoint_Press = false;
        private void priceToy_Press(object sender, KeyPressEventArgs e)
        {
            char number = e.KeyChar;
            if (this.priceToyBox.Text.IndexOf(',') < 0)
                this.flagPoint_Press = false;

            if (((!Char.IsDigit(number)) && (number != ',') && (number != 8))
                || ((number == ',') && (this.flagPoint_Press)))
                e.Handled = true;
            if ((number == ',') && (!this.flagPoint_Press))
                this.flagPoint_Press = true;
        }

        private void valueFrom_Press(object sender, KeyPressEventArgs e)
        {
            char number = e.KeyChar;

            if (!Char.IsDigit(number) && (number != 8))
                e.Handled = true;
        }

        private void valueBefore_Press(object sender, KeyPressEventArgs e)
        {
            char number = e.KeyChar;

            if (!Char.IsDigit(number) && (number != 8))
                e.Handled = true;
        }
    }
}
