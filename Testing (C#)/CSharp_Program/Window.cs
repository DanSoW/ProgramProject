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
using System.Collections;

namespace CSharp_Program
{
    public partial class Window : Form
    {
        public Window()
        {
            InitializeComponent();
            
        }

        private bool checkStringNumber(string text) //проверка текста на содержание корректного числа
        {
            if (text.Length == 0)
                return false;
            text = text.Trim();
            int counterMinus = 0;
            for(int i = 0; i < text.Length; i++)
            {
                if ((!Char.IsDigit(text[i])) && (text[i] != '-'))
                    return false;
                else if (text[i] == '-')
                    counterMinus++;
            }
            if ((counterMinus == 1) && (text[0] != '-'))
                return false;

            return (counterMinus == 0) || ((counterMinus == 1) && (text[0] == '-'));
        }
        
        private bool checkStringMatrix(string text) //Проверка текста матрицы на корректность
        {
            string[] stringMatrix = text.Split(new string[] { Environment.NewLine, "\n" }, StringSplitOptions.RemoveEmptyEntries);
            if (stringMatrix.Length == 0)
                return false;

            for(int i = 0; i < stringMatrix.Length; i++)
            {

                string[] stringValues = stringMatrix[i].Trim(new char[] { ' ' })
                    .Split(new string[] { " " }, StringSplitOptions.RemoveEmptyEntries);

                if (stringMatrix.Length != stringValues.Length)
                    return false;

                for (int j = 0; j < stringValues.Length; j++)
                    if (!checkStringNumber(stringValues[j]))
                        return false;
            }

            return true;
        }

        private Matrix textToMatrix(string text) //Преобразование текста в матрицу
        {
            if (!checkStringMatrix(text))
                return null;

            string[] stringMatrix = text.Split(new string[] { Environment.NewLine, "\n" }, StringSplitOptions.RemoveEmptyEntries);

            Matrix matrix = new Matrix(stringMatrix.Length);
            for(int i = 0; i < stringMatrix.Length; i++)
            {
                string[] stringValues = stringMatrix[i].Trim(new char[] { ' ' }).Split(new string[] { " " }, StringSplitOptions.RemoveEmptyEntries);
                for (int j = 0; j < stringValues.Length; j++)
                    matrix[i][j] = int.Parse(stringValues[j]);
            }

            return matrix;
        }

        private string matrixToText(Matrix matrix) //Преобразование матрицы в текст
        {
            if ((matrix == null) || (matrix.Size <= 0))
                return string.Empty;

            string text = "";
            for(int i = 0; i < matrix.Size; i++)
            {
                for (int j = 0; j < matrix.Size; j++)
                    text += matrix[i][j].ToString() + " ";
                text += "\n";
            }

            return text;
        }

        private void button4_Click(object sender, EventArgs e) //Вычисление результирующей матрицы
        {
            if((richTextBox1.Text.Length == 0) 
                || (richTextBox2.Text.Length == 0) 
                || (richTextBox3.Text.Length == 0)
                || (textBox1.Text.Length == 0))
            {
                MessageBox.Show("Ошибка: не все поля заполнены");
                return;
            }

            richTextBox4.Text = string.Empty;

            Matrix matrixA = textToMatrix(richTextBox1.Text), matrixB = textToMatrix(richTextBox2.Text),
                matrixC = textToMatrix(richTextBox3.Text);
            int T = int.Parse(textBox1.Text);

            if((matrixA == null) || (matrixB == null) || (matrixC == null))
            {
                MessageBox.Show("Ошибка: введены не корректные данные - матрицы должны быть квадратными, одного размера и содержать только целые числа");
            }

            Matrix result = Logic.getGlobalResult(matrixA, matrixB, matrixC, T);

            richTextBox4.Text = matrixToText(result);
        }

        private void textBox1_KeyPress(object sender, KeyPressEventArgs e) //Запись в T только чисел с возможностью отчистки
        {
            char number = e.KeyChar;

            if ((!Char.IsDigit(number)) && (number != 8))
            {
                e.Handled = true;
            }
        }

        private void button6_Click(object sender, EventArgs e) //Очистка
        {
            richTextBox1.Text = String.Empty;
            richTextBox2.Text = String.Empty;
            richTextBox3.Text = String.Empty;
            richTextBox4.Text = string.Empty;
            textBox1.Text = String.Empty;
        }

        private void button2_Click(object sender, EventArgs e) //Сохранение данных в файл
        {
            if ((richTextBox1.Text.Length == 0)
                   || (richTextBox2.Text.Length == 0)
                   || (richTextBox3.Text.Length == 0)
                   || (textBox1.Text.Length == 0))
            {
                MessageBox.Show("Ошибка: не все поля заполнены");
                return;
            }

            if ((!checkStringMatrix(richTextBox1.Text)) || (!checkStringMatrix(richTextBox2.Text)) || (!checkStringMatrix(richTextBox3.Text)))
            {
                MessageBox.Show("Ошибка: введены не корректные данные - матрицы должны быть квадратными, одного размера и содержать только целые числа");
            }

            string text = textToMatrix(richTextBox1.Text).Size.ToString() + "\n" + textBox1.Text + "\n"
                    + richTextBox1.Text.Trim(new char[] { '\n' }) + "\n" + richTextBox2.Text.Trim(new char[] { '\n' })
                    + "\n" + richTextBox3.Text.Trim(new char[] { '\n' }) + "\n";

            DialogResult result = MessageBox.Show("Указать путь сохранения самостоятельно?", "Система", MessageBoxButtons.YesNo);

            if (result == DialogResult.Yes)
            {
                SaveFileDialog saveFile = new SaveFileDialog();
                saveFile.Filter = "Text files(*.txt)|*.txt|All files(*.*)|*.*";
                if (saveFile.ShowDialog() == DialogResult.Cancel)
                {
                    MessageBox.Show("Отмена записи файла", "Система");
                    return;
                }
                System.IO.File.WriteAllText(saveFile.FileName, text);
            }
            else
            {
                System.IO.File.WriteAllText("..\\..\\data.txt", text);
            }

            MessageBox.Show("Данные сохранены!", "Система");
        }

        private void button3_Click(object sender, EventArgs e) //Считывание данных из файла
        {
            button6_Click(sender, e);
            DialogResult result = MessageBox.Show("Указать путь считывания самостоятельно?", "Система", MessageBoxButtons.YesNo);

            string[] text = null;
            if (result == DialogResult.Yes)
            {
                OpenFileDialog openFile = new OpenFileDialog();
                openFile.Filter = "Text files(*.txt)|*.txt|All files(*.*)|*.*";
                if (openFile.ShowDialog() == DialogResult.Cancel)
                {
                    MessageBox.Show("Отмена считывания из файла", "Система");
                    return;
                }
                text = System.IO.File.ReadAllText(openFile.FileName)
                    .Split(new string[] { Environment.NewLine, "\n" }, StringSplitOptions.RemoveEmptyEntries);
            }
            else
            {
                text = System.IO.File.ReadAllText("..\\..\\data.txt")
                    .Split(new string[] { Environment.NewLine, "\n" }, StringSplitOptions.RemoveEmptyEntries);
            }

            int size = int.Parse(text[0]);
            textBox1.Text = text[1];

            for(int i = 2; i < (2+size); i++)
                richTextBox1.Text += text[i] + "\n";

            for(int i = (2+size); i < (2 + 2*size); i++)
                richTextBox2.Text += text[i] + "\n";

            for (int i = (2 + 2*size); i < (2 + 3 * size); i++)
                richTextBox3.Text += text[i] + "\n";

            MessageBox.Show("Данные считаны из файла", "Система");
        }
    }
}
