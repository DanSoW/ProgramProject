namespace KursProject
{
    partial class RequestForm
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
            this.allMaxPriceNameLabel = new System.Windows.Forms.Label();
            this.allMaxPriceBox = new System.Windows.Forms.TextBox();
            this.allMaxPriceButton = new System.Windows.Forms.Button();
            this.allPriceNameLabel = new System.Windows.Forms.Label();
            this.allNameToyBox = new System.Windows.Forms.TextBox();
            this.allNameButton = new System.Windows.Forms.Button();
            this.haveLabel1 = new System.Windows.Forms.Label();
            this.haveNameToyBox = new System.Windows.Forms.TextBox();
            this.haveLabel2 = new System.Windows.Forms.Label();
            this.havePriceToyBox = new System.Windows.Forms.TextBox();
            this.haveLabel3 = new System.Windows.Forms.Label();
            this.haveValueFromBox = new System.Windows.Forms.TextBox();
            this.haveLabel4 = new System.Windows.Forms.Label();
            this.haveValueBeforeBox = new System.Windows.Forms.TextBox();
            this.haveButton = new System.Windows.Forms.Button();
            this.ageLimitLabel = new System.Windows.Forms.Label();
            this.ageLimitBox = new System.Windows.Forms.TextBox();
            this.ageLimitButton = new System.Windows.Forms.Button();
            this.exitButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // allMaxPriceNameLabel
            // 
            this.allMaxPriceNameLabel.AutoSize = true;
            this.allMaxPriceNameLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F);
            this.allMaxPriceNameLabel.Location = new System.Drawing.Point(12, 48);
            this.allMaxPriceNameLabel.Name = "allMaxPriceNameLabel";
            this.allMaxPriceNameLabel.Size = new System.Drawing.Size(614, 13);
            this.allMaxPriceNameLabel.TabIndex = 0;
            this.allMaxPriceNameLabel.Text = "Выдать названия самых дорогих игрушек, цена которых отличается от цены самой доро" +
    "гой не более чем на величину:";
            // 
            // allMaxPriceBox
            // 
            this.allMaxPriceBox.Location = new System.Drawing.Point(647, 45);
            this.allMaxPriceBox.Name = "allMaxPriceBox";
            this.allMaxPriceBox.Size = new System.Drawing.Size(100, 20);
            this.allMaxPriceBox.TabIndex = 1;
            this.allMaxPriceBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.allMaxPriceBox_Press);
            // 
            // allMaxPriceButton
            // 
            this.allMaxPriceButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.allMaxPriceButton.Location = new System.Drawing.Point(647, 71);
            this.allMaxPriceButton.Name = "allMaxPriceButton";
            this.allMaxPriceButton.Size = new System.Drawing.Size(100, 30);
            this.allMaxPriceButton.TabIndex = 2;
            this.allMaxPriceButton.Text = "Обработать";
            this.allMaxPriceButton.UseVisualStyleBackColor = true;
            this.allMaxPriceButton.Click += new System.EventHandler(this.AllMaxPriceButton_Click);
            // 
            // allPriceNameLabel
            // 
            this.allPriceNameLabel.AutoSize = true;
            this.allPriceNameLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.allPriceNameLabel.Location = new System.Drawing.Point(12, 98);
            this.allPriceNameLabel.Name = "allPriceNameLabel";
            this.allPriceNameLabel.Size = new System.Drawing.Size(229, 17);
            this.allPriceNameLabel.TabIndex = 3;
            this.allPriceNameLabel.Text = "Цены всех игрушек с названием: ";
            // 
            // allNameToyBox
            // 
            this.allNameToyBox.Location = new System.Drawing.Point(247, 98);
            this.allNameToyBox.Name = "allNameToyBox";
            this.allNameToyBox.Size = new System.Drawing.Size(100, 20);
            this.allNameToyBox.TabIndex = 4;
            // 
            // allNameButton
            // 
            this.allNameButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.allNameButton.Location = new System.Drawing.Point(353, 94);
            this.allNameButton.Name = "allNameButton";
            this.allNameButton.Size = new System.Drawing.Size(100, 27);
            this.allNameButton.TabIndex = 5;
            this.allNameButton.Text = "Обработать";
            this.allNameButton.UseVisualStyleBackColor = true;
            this.allNameButton.Click += new System.EventHandler(this.AllNameButton_Click);
            // 
            // haveLabel1
            // 
            this.haveLabel1.AutoSize = true;
            this.haveLabel1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.haveLabel1.Location = new System.Drawing.Point(12, 172);
            this.haveLabel1.Name = "haveLabel1";
            this.haveLabel1.Size = new System.Drawing.Size(147, 17);
            this.haveLabel1.TabIndex = 6;
            this.haveLabel1.Text = "Имеется ли игрушка ";
            // 
            // haveNameToyBox
            // 
            this.haveNameToyBox.Location = new System.Drawing.Point(165, 172);
            this.haveNameToyBox.Name = "haveNameToyBox";
            this.haveNameToyBox.Size = new System.Drawing.Size(100, 20);
            this.haveNameToyBox.TabIndex = 7;
            // 
            // haveLabel2
            // 
            this.haveLabel2.AutoSize = true;
            this.haveLabel2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.haveLabel2.Location = new System.Drawing.Point(271, 171);
            this.haveLabel2.Name = "haveLabel2";
            this.haveLabel2.Size = new System.Drawing.Size(63, 17);
            this.haveLabel2.TabIndex = 8;
            this.haveLabel2.Text = "с ценой ";
            // 
            // havePriceToyBox
            // 
            this.havePriceToyBox.Location = new System.Drawing.Point(340, 172);
            this.havePriceToyBox.Name = "havePriceToyBox";
            this.havePriceToyBox.Size = new System.Drawing.Size(100, 20);
            this.havePriceToyBox.TabIndex = 9;
            this.havePriceToyBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.havePriceBox_Press);
            // 
            // haveLabel3
            // 
            this.haveLabel3.AutoSize = true;
            this.haveLabel3.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.haveLabel3.Location = new System.Drawing.Point(446, 173);
            this.haveLabel3.Name = "haveLabel3";
            this.haveLabel3.Size = new System.Drawing.Size(71, 17);
            this.haveLabel3.TabIndex = 10;
            this.haveLabel3.Text = "детям от ";
            // 
            // haveValueFromBox
            // 
            this.haveValueFromBox.Location = new System.Drawing.Point(523, 172);
            this.haveValueFromBox.Name = "haveValueFromBox";
            this.haveValueFromBox.Size = new System.Drawing.Size(32, 20);
            this.haveValueFromBox.TabIndex = 11;
            this.haveValueFromBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.haveValueFromBox_Press);
            // 
            // haveLabel4
            // 
            this.haveLabel4.AutoSize = true;
            this.haveLabel4.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.haveLabel4.Location = new System.Drawing.Point(561, 173);
            this.haveLabel4.Name = "haveLabel4";
            this.haveLabel4.Size = new System.Drawing.Size(24, 17);
            this.haveLabel4.TabIndex = 12;
            this.haveLabel4.Text = "до";
            // 
            // haveValueBeforeBox
            // 
            this.haveValueBeforeBox.Location = new System.Drawing.Point(591, 172);
            this.haveValueBeforeBox.Name = "haveValueBeforeBox";
            this.haveValueBeforeBox.Size = new System.Drawing.Size(33, 20);
            this.haveValueBeforeBox.TabIndex = 13;
            this.haveValueBeforeBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.haveValueBeforeBox_Press);
            // 
            // haveButton
            // 
            this.haveButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.haveButton.Location = new System.Drawing.Point(643, 166);
            this.haveButton.Name = "haveButton";
            this.haveButton.Size = new System.Drawing.Size(100, 31);
            this.haveButton.TabIndex = 14;
            this.haveButton.Text = "Обработать";
            this.haveButton.UseVisualStyleBackColor = true;
            this.haveButton.Click += new System.EventHandler(this.HaveButton_Click);
            // 
            // ageLimitLabel
            // 
            this.ageLimitLabel.AutoSize = true;
            this.ageLimitLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.ageLimitLabel.Location = new System.Drawing.Point(12, 249);
            this.ageLimitLabel.Name = "ageLimitLabel";
            this.ageLimitLabel.Size = new System.Drawing.Size(270, 17);
            this.ageLimitLabel.TabIndex = 15;
            this.ageLimitLabel.Text = "Возрастные границы игрушки с именем";
            // 
            // ageLimitBox
            // 
            this.ageLimitBox.Location = new System.Drawing.Point(288, 248);
            this.ageLimitBox.Name = "ageLimitBox";
            this.ageLimitBox.Size = new System.Drawing.Size(100, 20);
            this.ageLimitBox.TabIndex = 16;
            // 
            // ageLimitButton
            // 
            this.ageLimitButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.ageLimitButton.Location = new System.Drawing.Point(395, 244);
            this.ageLimitButton.Name = "ageLimitButton";
            this.ageLimitButton.Size = new System.Drawing.Size(103, 28);
            this.ageLimitButton.TabIndex = 17;
            this.ageLimitButton.Text = "Обработать";
            this.ageLimitButton.UseVisualStyleBackColor = true;
            this.ageLimitButton.Click += new System.EventHandler(this.AgeLimitButton_Click);
            // 
            // exitButton
            // 
            this.exitButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.exitButton.Location = new System.Drawing.Point(12, 324);
            this.exitButton.Name = "exitButton";
            this.exitButton.Size = new System.Drawing.Size(75, 31);
            this.exitButton.TabIndex = 18;
            this.exitButton.Text = "Выход";
            this.exitButton.UseVisualStyleBackColor = true;
            this.exitButton.Click += new System.EventHandler(this.ExitButton_Click);
            // 
            // RequestForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 367);
            this.Controls.Add(this.exitButton);
            this.Controls.Add(this.ageLimitButton);
            this.Controls.Add(this.ageLimitBox);
            this.Controls.Add(this.ageLimitLabel);
            this.Controls.Add(this.haveButton);
            this.Controls.Add(this.haveValueBeforeBox);
            this.Controls.Add(this.haveLabel4);
            this.Controls.Add(this.haveValueFromBox);
            this.Controls.Add(this.haveLabel3);
            this.Controls.Add(this.havePriceToyBox);
            this.Controls.Add(this.haveLabel2);
            this.Controls.Add(this.haveNameToyBox);
            this.Controls.Add(this.haveLabel1);
            this.Controls.Add(this.allNameButton);
            this.Controls.Add(this.allNameToyBox);
            this.Controls.Add(this.allPriceNameLabel);
            this.Controls.Add(this.allMaxPriceButton);
            this.Controls.Add(this.allMaxPriceBox);
            this.Controls.Add(this.allMaxPriceNameLabel);
            this.Name = "RequestForm";
            this.Text = "Обработка запросов";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label allMaxPriceNameLabel;
        private System.Windows.Forms.TextBox allMaxPriceBox;
        private System.Windows.Forms.Button allMaxPriceButton;
        private System.Windows.Forms.Label allPriceNameLabel;
        private System.Windows.Forms.TextBox allNameToyBox;
        private System.Windows.Forms.Button allNameButton;
        private System.Windows.Forms.Label haveLabel1;
        private System.Windows.Forms.TextBox haveNameToyBox;
        private System.Windows.Forms.Label haveLabel2;
        private System.Windows.Forms.TextBox havePriceToyBox;
        private System.Windows.Forms.Label haveLabel3;
        private System.Windows.Forms.TextBox haveValueFromBox;
        private System.Windows.Forms.Label haveLabel4;
        private System.Windows.Forms.TextBox haveValueBeforeBox;
        private System.Windows.Forms.Button haveButton;
        private System.Windows.Forms.Label ageLimitLabel;
        private System.Windows.Forms.TextBox ageLimitBox;
        private System.Windows.Forms.Button ageLimitButton;
        private System.Windows.Forms.Button exitButton;
    }
}