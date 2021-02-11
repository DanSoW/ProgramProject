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
    public partial class RequestForm : Form
    {
        public RequestForm()
        {
            InitializeComponent();
            this.FormClosed += ExitButton_Click;
            this.haveValueFromBox.MaxLength = 2;
            this.haveValueBeforeBox.MaxLength = 2;
            this.havePriceToyBox.MaxLength = 10;
            this.allMaxPriceBox.MaxLength = 10;
        }

        private void ExitButton_Click(object sender, EventArgs e)
        {
            this.Hide();
            ((MainForm)(Application.OpenForms[0])).ViewStateForm.OpenFormRequest = false;
        }

        private void AgeLimitButton_Click(object sender, EventArgs e)
        {
            this.ageLimitBox.Text = this.ageLimitBox.Text.Trim(' ');
            if (this.ageLimitBox.Text.Length <= 0){
                MessageBox.Show("Необходимо заполнить поле для ввода данных!", "Ошибка");
                return;
            }

            List<UserEntry> listUser = ((MainForm)(Application.OpenForms[0])).ViewStateForm.AllEntry;

            int index = (-1);
            for (int i = 0; (i < listUser.Count) && (index < 0); i++)
                if (listUser[i].name_toy.Equals(this.ageLimitBox.Text))
                    index = i;

            if (index < 0)
            {
                MessageBox.Show("Игрушки с таким именем в базе данных нет", "Уведомление");
                this.ageLimitBox.Text = "";
                return;
            }

            List<int> indexList = new List<int>();
            indexList.Add(index);
            for (int i = (index + 1); (i < listUser.Count); i++)
                if (listUser[i].name_toy.Equals(this.ageLimitBox.Text))
                    indexList.Add(i);

            string data_toys = "";
            for (int i = 0; i < indexList.Count; i++)
                data_toys += "от " + listUser[indexList[i]].valueFrom.ToString()
                    + " до " + listUser[indexList[i]].valueBefore.ToString() + "\n";

            MessageBox.Show("Возрастные границы игрушки  " + this.ageLimitBox.Text + ":\n\n"
                + data_toys + "\n", "Информация");

            this.ageLimitBox.Text = "";
        }

        private void HaveButton_Click(object sender, EventArgs e)
        {
            this.haveNameToyBox.Text = this.haveNameToyBox.Text.Trim(' ');

            if ((this.haveNameToyBox.Text.Length <= 0) || (this.havePriceToyBox.Text.Length <= 0)
                || (this.haveValueFromBox.Text.Length <= 0) || (this.haveValueBeforeBox.Text.Length <= 0))
            {
                MessageBox.Show("Необходимо заполнить поля для ввода данных!", "Ошибка");
                return;
            }

            List<UserEntry> listUser = ((MainForm)(Application.OpenForms[0])).ViewStateForm.AllEntry;

            int counter = 0;
            for (int i = 0; (i < listUser.Count); i++)
                if (listUser[i].name_toy.Equals(this.haveNameToyBox.Text)
                    && listUser[i].price_toy.Equals(System.Convert.ToDouble(this.havePriceToyBox.Text))
                    && listUser[i].valueFrom.Equals(System.Convert.ToInt32(this.haveValueFromBox.Text))
                    && listUser[i].valueBefore.Equals(System.Convert.ToInt32(this.haveValueBeforeBox.Text)))
                    counter++;

            MessageBox.Show("Количество записей удовлетворяющих условию запроса: " + counter.ToString(), "Информация");
            this.haveNameToyBox.Text = "";
            this.havePriceToyBox.Text = "";
            this.haveValueFromBox.Text = "";
            this.haveValueBeforeBox.Text = "";
        }

        private void AllNameButton_Click(object sender, EventArgs e)
        {
            this.allNameToyBox.Text = this.allNameToyBox.Text.Trim(' ');
            if (this.allNameToyBox.Text.Length <= 0)
            {
                MessageBox.Show("Необходимо заполнить поле для ввода данных!", "Ошибка");
                return;
            }

            List<UserEntry> listUser = ((MainForm)(Application.OpenForms[0])).ViewStateForm.AllEntry;

            int index = (-1);
            for (int i = 0; (i < listUser.Count) && (index < 0); i++)
                if (listUser[i].name_toy.Equals(this.allNameToyBox.Text))
                    index = i;

            if (index < 0)
            {
                MessageBox.Show("Игрушки с таким именем в базе данных нет", "Уведомление");
                this.allNameToyBox.Text = "";
                return;
            }

            string allPrice = "";
            for (int i = 0; (i < listUser.Count); i++)
                if (listUser[i].name_toy.Equals(this.allNameToyBox.Text))
                    allPrice += listUser[i].price_toy.ToString() + " руб.\n";
            MessageBox.Show("Цены всех игрушек с именем " + this.allNameToyBox.Text + ": \n\n" + allPrice + "\n", "Информация");

            this.allNameToyBox.Text = "";
        }

        private void AllMaxPriceButton_Click(object sender, EventArgs e)
        {
            if(this.allMaxPriceBox.Text.Length <= 0)
            {
                MessageBox.Show("Необходимо заполнить поле для ввода данных!", "Ошибка");
                return;
            }

            List<UserEntry> listUser = ((MainForm)(Application.OpenForms[0])).ViewStateForm.AllEntry;
            double max_price = ((MainForm)(Application.OpenForms[0])).ViewStateForm.MaxPrice,
                def_price = System.Convert.ToDouble(this.allMaxPriceBox.Text);

            string data_toys = "";

            for (int i = 0; i < listUser.Count; i++)
                if ((listUser[i].price_toy + def_price).Equals(max_price))
                    data_toys += listUser[i].name_toy + "    " +
                        listUser[i].price_toy.ToString() + " .руб\n";

            this.allMaxPriceBox.Text = "";
            if (data_toys.Length <= 0)
            {
                MessageBox.Show("Записей удовлетворяющих данному запросу в базе данных нет", "Уведомление");
                return;
            }

            MessageBox.Show("Записи удовлетворяющие данному запросу: \n\n" + data_toys + "\n\n", "Информация");

        }

        private bool flagPointHaveBox_Press = false;
        private void havePriceBox_Press(object sender, KeyPressEventArgs e)
        {
            char number = e.KeyChar;
            if (this.havePriceToyBox.Text.IndexOf(',') < 0)
                this.flagPointHaveBox_Press = false;

            if (((!Char.IsDigit(number)) && (number != ',') && (number != 8))
                || ((number == ',') && (this.flagPointHaveBox_Press)))
                e.Handled = true;
            if ((number == ',') && (!this.flagPointHaveBox_Press))
                this.flagPointHaveBox_Press = true;
        }

        private void haveValueFromBox_Press(object sender, KeyPressEventArgs e)
        {
            char number = e.KeyChar;

            if (!Char.IsDigit(number) && (number != 8))
                e.Handled = true;
        }

        private void haveValueBeforeBox_Press(object sender, KeyPressEventArgs e)
        {
            char number = e.KeyChar;

            if (!Char.IsDigit(number) && (number != 8))
                e.Handled = true;
        }

        private bool flagPointPriceBox_Press = false;
        private void allMaxPriceBox_Press(object sender, KeyPressEventArgs e)
        {
            char number = e.KeyChar;
            if (this.allMaxPriceBox.Text.IndexOf(',') < 0)
                this.flagPointPriceBox_Press = false;

            if (((!Char.IsDigit(number)) && (number != ',') && (number != 8))
                || ((number == ',') && (this.flagPointPriceBox_Press)))
                e.Handled = true;
            if ((number == ',') && (!this.flagPointPriceBox_Press))
                this.flagPointPriceBox_Press = true;
        }
    }

    public partial class MainForm : Form
    {
        public ViewStatForm ViewStateForm
        {
            get
            {
                return this.formStatView;
            }
        }
    }
    public partial class ViewStatForm : Form
    {
        public double MaxPrice
        {
            get
            {
                if (this.maxPrice.Text.Length <= 0)
                    return 0;
                return System.Convert.ToDouble(this.maxPrice.Text);
            }
        }
        public List<UserEntry> AllEntry
        {
            get
            {
                return this.userEntries;
            }
        }
        public bool OpenFormRequest
        {
            get
            {
                return this.openRequestForm;
            }
            set
            {
                this.openRequestForm = value;
            }
        }
    }
}
