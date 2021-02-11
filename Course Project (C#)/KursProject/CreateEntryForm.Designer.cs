namespace KursProject
{
    partial class CreateEntryForm
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
            this.label1 = new System.Windows.Forms.Label();
            this.exitButton = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.nameToyBox = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.priceToyBox = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.valueFromBox = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.valueBeforeBox = new System.Windows.Forms.TextBox();
            this.addEntryButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F);
            this.label1.Location = new System.Drawing.Point(266, 28);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(264, 31);
            this.label1.TabIndex = 0;
            this.label1.Text = "Добавление записи";
            // 
            // exitButton
            // 
            this.exitButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.exitButton.Location = new System.Drawing.Point(23, 302);
            this.exitButton.Name = "exitButton";
            this.exitButton.Size = new System.Drawing.Size(80, 30);
            this.exitButton.TabIndex = 1;
            this.exitButton.Text = "Выход";
            this.exitButton.UseVisualStyleBackColor = true;
            this.exitButton.Click += new System.EventHandler(this.ExitButton_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.label2.Location = new System.Drawing.Point(169, 97);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(134, 17);
            this.label2.TabIndex = 2;
            this.label2.Text = "Название игрушки:";
            // 
            // nameToyBox
            // 
            this.nameToyBox.Location = new System.Drawing.Point(322, 97);
            this.nameToyBox.Name = "nameToyBox";
            this.nameToyBox.Size = new System.Drawing.Size(275, 20);
            this.nameToyBox.TabIndex = 3;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.label3.Location = new System.Drawing.Point(169, 145);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(140, 17);
            this.label3.TabIndex = 4;
            this.label3.Text = "Стоимость игрушки:";
            // 
            // priceToyBox
            // 
            this.priceToyBox.Location = new System.Drawing.Point(322, 145);
            this.priceToyBox.Name = "priceToyBox";
            this.priceToyBox.Size = new System.Drawing.Size(275, 20);
            this.priceToyBox.TabIndex = 5;
            this.priceToyBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.priceToy_Press);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.label4.Location = new System.Drawing.Point(169, 191);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(181, 17);
            this.label4.TabIndex = 6;
            this.label4.Text = "Возрастные ограничения:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.label5.Location = new System.Drawing.Point(169, 225);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(27, 17);
            this.label5.TabIndex = 7;
            this.label5.Text = "от:";
            // 
            // valueFromBox
            // 
            this.valueFromBox.Location = new System.Drawing.Point(202, 225);
            this.valueFromBox.Name = "valueFromBox";
            this.valueFromBox.Size = new System.Drawing.Size(34, 20);
            this.valueFromBox.TabIndex = 8;
            this.valueFromBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.valueFrom_Press);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.label6.Location = new System.Drawing.Point(269, 225);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(28, 17);
            this.label6.TabIndex = 9;
            this.label6.Text = "до:";
            // 
            // valueBeforeBox
            // 
            this.valueBeforeBox.Location = new System.Drawing.Point(303, 224);
            this.valueBeforeBox.Name = "valueBeforeBox";
            this.valueBeforeBox.Size = new System.Drawing.Size(36, 20);
            this.valueBeforeBox.TabIndex = 10;
            this.valueBeforeBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.valueBefore_Press);
            // 
            // addEntryButton
            // 
            this.addEntryButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.addEntryButton.Location = new System.Drawing.Point(455, 222);
            this.addEntryButton.Name = "addEntryButton";
            this.addEntryButton.Size = new System.Drawing.Size(142, 25);
            this.addEntryButton.TabIndex = 11;
            this.addEntryButton.Text = "Добавить запись";
            this.addEntryButton.UseVisualStyleBackColor = true;
            this.addEntryButton.Click += new System.EventHandler(this.AddEntryButton_Click);
            // 
            // CreateEntryForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 352);
            this.Controls.Add(this.addEntryButton);
            this.Controls.Add(this.valueBeforeBox);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.valueFromBox);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.priceToyBox);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.nameToyBox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.exitButton);
            this.Controls.Add(this.label1);
            this.Name = "CreateEntryForm";
            this.Text = "Добавление записи";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button exitButton;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox nameToyBox;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox priceToyBox;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox valueFromBox;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox valueBeforeBox;
        private System.Windows.Forms.Button addEntryButton;
        private UserEntry dynamicEntry;
    }
}