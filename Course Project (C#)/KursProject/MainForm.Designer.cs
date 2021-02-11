namespace KursProject
{
    partial class MainForm
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.label1 = new System.Windows.Forms.Label();
            this.addButton = new System.Windows.Forms.Button();
            this.deleteButton = new System.Windows.Forms.Button();
            this.openButton = new System.Windows.Forms.Button();
            this.checkedListFile = new System.Windows.Forms.CheckedListBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.closeFileButton = new System.Windows.Forms.Button();
            this.setDataButton = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.viewEntryButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(800, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.label1.Location = new System.Drawing.Point(26, 52);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(230, 17);
            this.label1.TabIndex = 1;
            this.label1.Text = "Сведения о файлах базы данных:";
            // 
            // addButton
            // 
            this.addButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.addButton.Location = new System.Drawing.Point(276, 97);
            this.addButton.Name = "addButton";
            this.addButton.Size = new System.Drawing.Size(84, 32);
            this.addButton.TabIndex = 3;
            this.addButton.Text = "Добавить";
            this.addButton.UseVisualStyleBackColor = true;
            this.addButton.Click += new System.EventHandler(this.addButton_Click);
            // 
            // deleteButton
            // 
            this.deleteButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.deleteButton.Location = new System.Drawing.Point(276, 357);
            this.deleteButton.Name = "deleteButton";
            this.deleteButton.Size = new System.Drawing.Size(84, 30);
            this.deleteButton.TabIndex = 4;
            this.deleteButton.Text = "Удалить";
            this.deleteButton.UseVisualStyleBackColor = true;
            this.deleteButton.Click += new System.EventHandler(this.deleteButton_Click);
            // 
            // openButton
            // 
            this.openButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.openButton.Location = new System.Drawing.Point(276, 145);
            this.openButton.Name = "openButton";
            this.openButton.Size = new System.Drawing.Size(84, 30);
            this.openButton.TabIndex = 5;
            this.openButton.Text = "Открыть";
            this.openButton.UseVisualStyleBackColor = true;
            this.openButton.Click += new System.EventHandler(this.openButton_Click);
            // 
            // checkedListFile
            // 
            this.checkedListFile.FormattingEnabled = true;
            this.checkedListFile.Location = new System.Drawing.Point(29, 97);
            this.checkedListFile.Name = "checkedListFile";
            this.checkedListFile.Size = new System.Drawing.Size(227, 289);
            this.checkedListFile.TabIndex = 7;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.label2.Location = new System.Drawing.Point(403, 97);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(119, 17);
            this.label2.TabIndex = 8;
            this.label2.Text = "Открытый файл:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.label3.Location = new System.Drawing.Point(529, 97);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(0, 17);
            this.label3.TabIndex = 9;
            // 
            // closeFileButton
            // 
            this.closeFileButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.closeFileButton.Location = new System.Drawing.Point(406, 192);
            this.closeFileButton.Name = "closeFileButton";
            this.closeFileButton.Size = new System.Drawing.Size(75, 30);
            this.closeFileButton.TabIndex = 10;
            this.closeFileButton.Text = "Закрыть";
            this.closeFileButton.UseVisualStyleBackColor = true;
            this.closeFileButton.Click += new System.EventHandler(this.CloseFileButton_Click);
            // 
            // setDataButton
            // 
            this.setDataButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.setDataButton.Location = new System.Drawing.Point(612, 192);
            this.setDataButton.Name = "setDataButton";
            this.setDataButton.Size = new System.Drawing.Size(147, 30);
            this.setDataButton.TabIndex = 11;
            this.setDataButton.Text = "Добавить запись";
            this.setDataButton.UseVisualStyleBackColor = true;
            this.setDataButton.Click += new System.EventHandler(this.SetDataButton_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.label4.Location = new System.Drawing.Point(403, 135);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(196, 17);
            this.label4.TabIndex = 12;
            this.label4.Text = "Общее количество записей:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.label5.Location = new System.Drawing.Point(609, 135);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(0, 17);
            this.label5.TabIndex = 13;
            // 
            // viewEntryButton
            // 
            this.viewEntryButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.viewEntryButton.Location = new System.Drawing.Point(457, 44);
            this.viewEntryButton.Name = "viewEntryButton";
            this.viewEntryButton.Size = new System.Drawing.Size(254, 32);
            this.viewEntryButton.TabIndex = 14;
            this.viewEntryButton.Text = "Просмотр статистики записи";
            this.viewEntryButton.UseVisualStyleBackColor = true;
            this.viewEntryButton.Click += new System.EventHandler(this.ViewEntryButton_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.viewEntryButton);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.setDataButton);
            this.Controls.Add(this.closeFileButton);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.checkedListFile);
            this.Controls.Add(this.openButton);
            this.Controls.Add(this.deleteButton);
            this.Controls.Add(this.addButton);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "MainForm";
            this.Text = "База данных";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button addButton;
        private System.Windows.Forms.Button deleteButton;
        private System.Windows.Forms.Button openButton;
        private System.Windows.Forms.CheckedListBox checkedListFile;

        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button closeFileButton;
        private System.Windows.Forms.Button setDataButton;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button viewEntryButton;

        /*Характеристика панели:
         в палени будет отображаться файлы, которые когда-либо были открыты с помощью данной программы. Это будет
         коллекция строк, хранящих адреса к файлам. Эту коллекцию можно пополнять и изменять.*/
        /*Что реализует данная программа: 
         1) Решает задачу курсовой работы с ОДНИМ ФАЙЛОМ.
         2) Позваляет решать задачу с множеством других файлов.
         3) Позваляет сравнивать данные в области одного файла, и в межфайловой области
         */
    }
}

