namespace KursProject
{
    partial class ViewStatForm
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
            this.dataBaseView = new System.Windows.Forms.DataGridView();
            this.DB_NameToy = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.DB_PriceToy = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.DB_FromAndBefore = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.topBaseDataText = new System.Windows.Forms.Label();
            this.exitButton = new System.Windows.Forms.Button();
            this.setEntryButton = new System.Windows.Forms.Button();
            this.deleteButton = new System.Windows.Forms.Button();
            this.maxLabel = new System.Windows.Forms.Label();
            this.minLabel = new System.Windows.Forms.Label();
            this.maxPLabel = new System.Windows.Forms.Label();
            this.minPLabel = new System.Windows.Forms.Label();
            this.nameMaxPriceToy = new System.Windows.Forms.Label();
            this.maxPrice = new System.Windows.Forms.Label();
            this.nameMinPriceToy = new System.Windows.Forms.Label();
            this.minPrice = new System.Windows.Forms.Label();
            this.procButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataBaseView)).BeginInit();
            this.SuspendLayout();
            // 
            // dataBaseView
            // 
            this.dataBaseView.AllowUserToAddRows = false;
            this.dataBaseView.AllowUserToOrderColumns = true;
            this.dataBaseView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataBaseView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.DB_NameToy,
            this.DB_PriceToy,
            this.DB_FromAndBefore});
            this.dataBaseView.Location = new System.Drawing.Point(13, 52);
            this.dataBaseView.Name = "dataBaseView";
            this.dataBaseView.Size = new System.Drawing.Size(363, 300);
            this.dataBaseView.TabIndex = 0;
            this.dataBaseView.RowPrePaint += new System.Windows.Forms.DataGridViewRowPrePaintEventHandler(this.dbPrePaint);
            // 
            // DB_NameToy
            // 
            this.DB_NameToy.HeaderText = "Имя игрушки";
            this.DB_NameToy.Name = "DB_NameToy";
            // 
            // DB_PriceToy
            // 
            this.DB_PriceToy.HeaderText = "Цена";
            this.DB_PriceToy.Name = "DB_PriceToy";
            // 
            // DB_FromAndBefore
            // 
            this.DB_FromAndBefore.HeaderText = "Возрастные ограничения";
            this.DB_FromAndBefore.Name = "DB_FromAndBefore";
            // 
            // topBaseDataText
            // 
            this.topBaseDataText.AutoSize = true;
            this.topBaseDataText.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F);
            this.topBaseDataText.Location = new System.Drawing.Point(134, 9);
            this.topBaseDataText.Name = "topBaseDataText";
            this.topBaseDataText.Size = new System.Drawing.Size(78, 25);
            this.topBaseDataText.TabIndex = 1;
            this.topBaseDataText.Text = "Записи";
            // 
            // exitButton
            // 
            this.exitButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.exitButton.Location = new System.Drawing.Point(12, 359);
            this.exitButton.Name = "exitButton";
            this.exitButton.Size = new System.Drawing.Size(79, 32);
            this.exitButton.TabIndex = 2;
            this.exitButton.Text = "Выход";
            this.exitButton.UseVisualStyleBackColor = true;
            this.exitButton.Click += new System.EventHandler(this.ExitButton_Click);
            // 
            // setEntryButton
            // 
            this.setEntryButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.setEntryButton.Location = new System.Drawing.Point(261, 359);
            this.setEntryButton.Name = "setEntryButton";
            this.setEntryButton.Size = new System.Drawing.Size(115, 32);
            this.setEntryButton.TabIndex = 3;
            this.setEntryButton.Text = "Добавить";
            this.setEntryButton.UseVisualStyleBackColor = true;
            this.setEntryButton.Click += new System.EventHandler(this.SetEntryButton_Click);
            // 
            // deleteButton
            // 
            this.deleteButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.deleteButton.Location = new System.Drawing.Point(118, 359);
            this.deleteButton.Name = "deleteButton";
            this.deleteButton.Size = new System.Drawing.Size(114, 32);
            this.deleteButton.TabIndex = 4;
            this.deleteButton.Text = "Удалить";
            this.deleteButton.UseVisualStyleBackColor = true;
            this.deleteButton.Click += new System.EventHandler(this.DeleteButton_Click);
            // 
            // maxLabel
            // 
            this.maxLabel.AutoSize = true;
            this.maxLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.maxLabel.Location = new System.Drawing.Point(394, 52);
            this.maxLabel.Name = "maxLabel";
            this.maxLabel.Size = new System.Drawing.Size(169, 17);
            this.maxLabel.TabIndex = 5;
            this.maxLabel.Text = "Самая дорогая игрушка:";
            // 
            // minLabel
            // 
            this.minLabel.AutoSize = true;
            this.minLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.minLabel.Location = new System.Drawing.Point(394, 156);
            this.minLabel.Name = "minLabel";
            this.minLabel.Size = new System.Drawing.Size(174, 17);
            this.minLabel.TabIndex = 6;
            this.minLabel.Text = "Самая дешёвая игрушка:";
            // 
            // maxPLabel
            // 
            this.maxPLabel.AutoSize = true;
            this.maxPLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.maxPLabel.Location = new System.Drawing.Point(516, 85);
            this.maxPLabel.Name = "maxPLabel";
            this.maxPLabel.Size = new System.Drawing.Size(47, 17);
            this.maxPLabel.TabIndex = 7;
            this.maxPLabel.Text = "Цена:";
            // 
            // minPLabel
            // 
            this.minPLabel.AutoSize = true;
            this.minPLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.minPLabel.Location = new System.Drawing.Point(521, 195);
            this.minPLabel.Name = "minPLabel";
            this.minPLabel.Size = new System.Drawing.Size(47, 17);
            this.minPLabel.TabIndex = 8;
            this.minPLabel.Text = "Цена:";
            // 
            // nameMaxPriceToy
            // 
            this.nameMaxPriceToy.AutoSize = true;
            this.nameMaxPriceToy.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.nameMaxPriceToy.Location = new System.Drawing.Point(570, 52);
            this.nameMaxPriceToy.Name = "nameMaxPriceToy";
            this.nameMaxPriceToy.Size = new System.Drawing.Size(0, 17);
            this.nameMaxPriceToy.TabIndex = 9;
            // 
            // maxPrice
            // 
            this.maxPrice.AutoSize = true;
            this.maxPrice.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.maxPrice.Location = new System.Drawing.Point(569, 85);
            this.maxPrice.Name = "maxPrice";
            this.maxPrice.Size = new System.Drawing.Size(0, 17);
            this.maxPrice.TabIndex = 10;
            // 
            // nameMinPriceToy
            // 
            this.nameMinPriceToy.AutoSize = true;
            this.nameMinPriceToy.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.nameMinPriceToy.Location = new System.Drawing.Point(570, 156);
            this.nameMinPriceToy.Name = "nameMinPriceToy";
            this.nameMinPriceToy.Size = new System.Drawing.Size(0, 17);
            this.nameMinPriceToy.TabIndex = 11;
            // 
            // minPrice
            // 
            this.minPrice.AutoSize = true;
            this.minPrice.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.minPrice.Location = new System.Drawing.Point(572, 195);
            this.minPrice.Name = "minPrice";
            this.minPrice.Size = new System.Drawing.Size(0, 17);
            this.minPrice.TabIndex = 12;
            // 
            // procButton
            // 
            this.procButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.procButton.Location = new System.Drawing.Point(397, 314);
            this.procButton.Name = "procButton";
            this.procButton.Size = new System.Drawing.Size(258, 38);
            this.procButton.TabIndex = 13;
            this.procButton.Text = "Обработка запросов";
            this.procButton.UseVisualStyleBackColor = true;
            this.procButton.Click += new System.EventHandler(this.ProcButton_Click);
            // 
            // ViewStatForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.procButton);
            this.Controls.Add(this.minPrice);
            this.Controls.Add(this.nameMinPriceToy);
            this.Controls.Add(this.maxPrice);
            this.Controls.Add(this.nameMaxPriceToy);
            this.Controls.Add(this.minPLabel);
            this.Controls.Add(this.maxPLabel);
            this.Controls.Add(this.minLabel);
            this.Controls.Add(this.maxLabel);
            this.Controls.Add(this.deleteButton);
            this.Controls.Add(this.setEntryButton);
            this.Controls.Add(this.exitButton);
            this.Controls.Add(this.topBaseDataText);
            this.Controls.Add(this.dataBaseView);
            this.Name = "ViewStatForm";
            this.Text = "Просмотр статистики";
            ((System.ComponentModel.ISupportInitialize)(this.dataBaseView)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataBaseView;
        private System.Windows.Forms.DataGridViewTextBoxColumn DB_NameToy;
        private System.Windows.Forms.DataGridViewTextBoxColumn DB_PriceToy;
        private System.Windows.Forms.DataGridViewTextBoxColumn DB_FromAndBefore;
        private System.Windows.Forms.Label topBaseDataText;
        private System.Windows.Forms.Button exitButton;
        private System.Windows.Forms.Button setEntryButton;
        private System.Windows.Forms.Button deleteButton;
        private System.Windows.Forms.Label maxLabel;
        private System.Windows.Forms.Label minLabel;
        private System.Windows.Forms.Label maxPLabel;
        private System.Windows.Forms.Label minPLabel;
        private System.Windows.Forms.Label nameMaxPriceToy;
        private System.Windows.Forms.Label maxPrice;
        private System.Windows.Forms.Label nameMinPriceToy;
        private System.Windows.Forms.Label minPrice;
        private System.Windows.Forms.Button procButton;
    }
}