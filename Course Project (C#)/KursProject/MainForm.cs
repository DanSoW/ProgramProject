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
    public partial class MainForm : Form
    {
        private CreateFileForm formCreateFile = null;
        private OpenFileForm formOpenFile = null;
        private CreateEntryForm formEntry = null;
        private ViewStatForm formStatView = null;

        public MainForm()
        {
            InitializeComponent();
 
            //Инициализация пунктов меню
            ToolStripMenuItem fileItem = new ToolStripMenuItem("Файл");
            ToolStripMenuItem createFile = new ToolStripMenuItem("Добавить файл"),
                openFile = new ToolStripMenuItem("Открыть файл");

            createFile.Click += this.createFile_Click;
            openFile.Click += this.openButton_Click;

            fileItem.DropDownItems.Add(createFile);
            fileItem.DropDownItems.Add(openFile);
            menuStrip1.Items.Add(fileItem);

            ToolStripMenuItem dataAbout = new ToolStripMenuItem("О программе");
            dataAbout.Click += AboutProgram;
            menuStrip1.Items.Add(dataAbout);

        }

        private void AboutProgram(object sender, EventArgs e)
        {
            MessageBox.Show("Автор программы: Солопов Даниил Дмитриевич\nНазвание программы: База данных игрушек" +
                "(курсовой проект)\n\nЧто делает программа: создаёт/добавляет файл для работы, открывает файл" +
                "осуществляет запись в файл данных, чтение данных из файла, просмотр данных.\n" +
                "Осуществляет возможность изменения содержимого файла путём удаления/добавления записей.");
        }

        private bool SetAllCountEntry()//устанавливает общее кол-во записей в файле
        {
            if ((!File.Exists(label3.Text)) || (label3.Text.Length <= 0))
                return false;

            StreamReader fileReader = new StreamReader(label3.Text);
            string[] allEntry = fileReader.ReadToEnd().Split('\n');
            fileReader.Close();
            
            for (int i = 0; i < (allEntry.Length - 1); i++)
                if ((!(allEntry[i].Split(' ')[0].Replace('_', ' ').Equals(label3.Text)))
                    || ((allEntry[i].Split(' ').Length != 5) && (allEntry[i].Split(' ').Length > 0)))
                    return false;
            this.label5.Text = (allEntry.Length - 1).ToString();

            return true;
        }
        private void addEntryButton_Click(object sender, EventArgs e)
        {
            if ((!File.Exists(label3.Text)) || (!formEntry.Entry.CheckAllAttribute()))
                return;
            StreamWriter fileWriter = new StreamWriter(label3.Text, true);

            fileWriter.WriteLine(label3.Text.Replace(' ', '_') + " "
                + formEntry.Entry.name_toy + " "
                + formEntry.Entry.price_toy.ToString() + " "
                + formEntry.Entry.valueFrom + " " 
                + formEntry.Entry.valueBefore);
            fileWriter.Close();

            if (!SetAllCountEntry())
            {
                label5.Text = "";
                label3.Text = "";
                MessageBox.Show("Данный файл не может быть обработан! " +
                    "Файл либо не принадлежит базе данных, либо данные в файле испорчены", "Ошибка");
                return;
            }

            MessageBox.Show("Запись добавлена!", "Уведомление");
            formEntry.Entry.SetStandartValues();
        }
        private void createFile_Create(object sender, EventArgs e)
        {
            if ((formCreateFile.NameFile == null) || (formCreateFile.NameFile == ""))
                return;
            formCreateFile.NameFile = formCreateFile.NameFile.Replace('_', ' ');

            for (int i = 0; i < this.checkedListFile.Items.Count; i++)
                if (formCreateFile.NameFile == this.checkedListFile.Items[i].ToString())
                {
                    MessageBox.Show("Файл с таким именем уже существует или добавлен!", "Ошибка");
                    return;
                }

            if (!File.Exists(formCreateFile.NameFile))
            {
                string name_directory = "";
                for (int i = 0, point = formCreateFile.NameFile.LastIndexOf('\\'); i < point; i++)
                    name_directory += formCreateFile.NameFile[i];

                if (!Directory.Exists(name_directory))
                {
                    try
                    {
                        Directory.CreateDirectory(name_directory);
                    }
                    catch (Exception)
                    {
                        MessageBox.Show("Введены не корректные данные!", "Ошибка");
                        formCreateFile.NameFile = "";
                        return;
                    }
                }

                File.Create(formCreateFile.NameFile).Close();
                if (!File.Exists(formCreateFile.NameFile))
                {
                    MessageBox.Show("Введены не корректные данные!", "Ошибка");
                    formCreateFile.NameFile = "";
                    return;
                }
            }
            this.checkedListFile.Items.Add(formCreateFile.NameFile);
            MessageBox.Show("Файл добавлен!", "Уведомление");
            formCreateFile.NameFile = "";
        }
        void createFile_Click(object sender, EventArgs e)
        {
            formCreateFile = new CreateFileForm();
            formCreateFile.Extension = ".txt";
            formCreateFile.CreateButton_CreateFileForm.Click += this.createFile_Create;
            formCreateFile.ViewButton_CreateFileForm.Click += this.createFile_Create;
            formCreateFile.Left = this.Left; // задаём открываемой форме позицию слева равную позиции текущей формы
            formCreateFile.Top = this.Top; // задаём открываемой форме позицию сверху равную позиции текущей формы
            formCreateFile.Show(); // отображаем CreateFileForm
            this.Hide(); // скрываем MainForm (this - текущая форма)
        }

        void openFile_Click(object sender, EventArgs e)
        {
            label5.Text = "";
            label3.Text = "";
            formOpenFile = new OpenFileForm();
            formOpenFile.OpenButton.Click += this.openFileButton_Click;
            formOpenFile.ViewButton.Click += this.openFileButton_Click;
            formOpenFile.Left = this.Left; 
            formOpenFile.Top = this.Top;
            formOpenFile.Activate();
            formOpenFile.Show();
            this.Hide();
        }

        private void addButton_Click(object sender, EventArgs e)
        {
            //добавление файла
            createFile_Click(sender, e);
        }

        private void openFileButton_Click(object sender, EventArgs e)
        {
            label5.Text = "";
            if ((!FileString.CheckFullNameFile(formOpenFile.NameFile, ".txt")))
            {
                formOpenFile.NameFile = "";
                return;
            }
            if ((!File.Exists(formOpenFile.NameFile)))
            {
                MessageBox.Show("Такого файла не существует!", "Ошибка");
                formOpenFile.NameFile = "";
                return;
            }

            label3.Text = formOpenFile.NameFile;
            if (!SetAllCountEntry())
            {
                label3.Text = "";
                MessageBox.Show("Данный файл не может быть обработан! " +
                    "Файл либо не принадлежит базе данных, либо данные в файле испорчены", "Ошибка");
                return;
            }
            MessageBox.Show("Файл открыт!", "Уведомление");
            formOpenFile.NameFile = "";
        }
        private void openButton_Click(object sender, EventArgs e)
        {
            //открытие файла
            label3.Text = "";
            if(this.checkedListFile.CheckedItems.Count <= 0)
            {
                openFile_Click(sender, e);
                return;
            }
        
            label3.Text = this.checkedListFile.CheckedItems[0].ToString();
            if (!SetAllCountEntry())
            {
                label3.Text = "";
                label5.Text = "";
                MessageBox.Show("Данный файл не может быть обработан! " +
                    "Файл либо не принадлежит базе данных, либо данные в файле испорчены", "Ошибка");
                return;
            }
            this.unCheckedListFile_Full();
            MessageBox.Show("Файл открыт!", "Уведомление");
        }

        private void unCheckedListFile_Full()
        {
            if (this.checkedListFile.CheckedItems.Count == 0)
                return;
            
            List<string> listString = new List<string>();
            for (int i = 0; i < this.checkedListFile.Items.Count; i++)
                listString.Add(this.checkedListFile.Items[i].ToString());
            this.checkedListFile.Items.Clear();
            for (int i = 0; i < listString.Count; i++)
                this.checkedListFile.Items.Add(listString[i]);
        }
        private void deleteButton_Click(object sender, EventArgs e)
        {
            if (this.checkedListFile.CheckedItems.Count == 0)
                return;
            if(MessageBox.Show("Удалить файл(-ы)?", "Действие", MessageBoxButtons.YesNo) == DialogResult.Yes)
            {
                while (this.checkedListFile.CheckedItems.Count > 0)
                {
                    if (this.checkedListFile.CheckedItems[0].ToString() == label3.Text)
                    {
                        label3.Text = "";
                        label5.Text = "";
                    }
                    if (File.Exists(this.checkedListFile.CheckedItems[0].ToString()))
                        File.Delete(this.checkedListFile.CheckedItems[0].ToString());
                    
                    this.checkedListFile.Items.Remove(this.checkedListFile.CheckedItems[0]);
                }
            }

            while(this.checkedListFile.CheckedItems.Count > 0)
                this.checkedListFile.Items.Remove(this.checkedListFile.CheckedItems[0]);
        }

        private void SetDataButton_Click(object sender, EventArgs e)
        {
            if(label3.Text.Length <= 0)
            {
                MessageBox.Show("Нет открытого файла для добавления записи!", "Ошибка");
                return;
            }
            formEntry = new CreateEntryForm();
            formEntry.AddEntryButton.Click += this.addEntryButton_Click;
            formEntry.Left = this.Left;
            formEntry.Top = this.Top;
            formEntry.Activate();
            formEntry.Show();
            this.Hide();
        }

        private void CloseFileButton_Click(object sender, EventArgs e)
        {
            this.label5.Text = "";
            this.label3.Text = "";
        }

        private void ViewEntryButton_Click(object sender, EventArgs e)
        {
            if(label3.Text.Length <= 0)
            {
                MessageBox.Show("Нет открытого файла для просмотра статистики!", "Ошибка");
                return;
            }
            formStatView = new ViewStatForm(label3.Text);
            formStatView.Left = this.Left;
            formStatView.Top = this.Top;
            formStatView.Activate();
            formStatView.Show();
            this.Hide();
        }

    }

    public partial class CreateFileForm : Form
    {
        public System.Windows.Forms.Button ViewButton_CreateFileForm
        {
            get
            {
                return this.viewButton;
            }
        }
        public System.Windows.Forms.Button CreateButton_CreateFileForm
        {
            get
            {
                return this.createButton;
            }
        }

        public System.Windows.Forms.Button ExitButton_CreateFileForm
        {
            get
            {
                return this.exitButton;
            }
        }
        public string Extension
        {
            set
            {
                this.extension = value;
            }

            get
            {
                return this.extension;
            }
        }

        public string NameFile
        {
            get
            {
                return this.openFile.FileName;
            }
            set
            {
                this.openFile.FileName = value;
            }
        }
    };

    public partial class OpenFileForm : Form
    {
        public string NameFile
        {
            get
            {
                return this.openFile.FileName;
            }
            set
            {
                this.openFile.FileName = value;
            }
        }

        public System.Windows.Forms.Button OpenButton
        {
            get
            {
                return this.openButton;
            }
        }

        public System.Windows.Forms.Button ViewButton
        {
            get
            {
                return this.viewButton;
            }
        }
    };

    public partial class CreateEntryForm : Form
    {
        public UserEntry Entry
        {
            get
            {
                return this.dynamicEntry;
            }
        }
        public System.Windows.Forms.Button AddEntryButton
        {
            get
            {
                return this.addEntryButton;
            }
        }
    };

}

