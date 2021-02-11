#include "tablewidget.h"
#include "ui_tablewidget.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDoubleValidator>

TableWidget::TableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableWidget)
{
    ui->setupUi(this);
    resize(600, 600);
    setWindowTitle("Таблица");
    QPushButton* window[3] = {new QPushButton("Выбор"),
                              new QPushButton("Картинка"),
                              new QPushButton("Таблица")};
    window[2]->setEnabled(false);

    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    for(short i = 0; i < 3; i++)
        hlayout->addWidget(window[i]);

    QStringList headers;
    headers << QString("Марка автомобиля")
            << QString("Номер")
            << QString("Вид")
            << QString("Пробег(км)")
            << QString("Число месяцев пробега")
            << QString("Средний пробег в месяц");

    ui->tableWidget->setColumnCount(count_column);
    ui->tableWidget->setColumnWidth(0, 150);
    ui->tableWidget->setColumnWidth((count_column-2), 150);
    ui->tableWidget->setColumnWidth((count_column-1), 150);
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    char dek_size = (count_column - 1);
    inputTableButton = new QLineEdit[dek_size];

    QLabel* label = new QLabel[dek_size];
    for(int i = 0; i < dek_size; i++)
        label[i].setText(headers[i] + ": ");
    label[0].setStyleSheet("margin-right: 301px;");
    label[1].setStyleSheet("margin-right: 365px;");
    label[2].setStyleSheet("margin-right: 377px;");
    label[3].setStyleSheet("margin-right: 340px;");
    label[4].setStyleSheet("margin-right: 278px;");

    QHBoxLayout* lb_layout = new QHBoxLayout[dek_size];
    for(int i = 0; i < dek_size; i++){
        lb_layout[i].addWidget(&label[i]);
        lb_layout[i].addWidget(&inputTableButton[i]);
    }

    inputTableButton[dek_size - 1].setValidator(new QRegExpValidator(QRegExp("^([1-9][0-9]*|0)(\\.)[0-9]{2}"), this));
    inputTableButton[dek_size - 2].setValidator(new QRegExpValidator(QRegExp("^([1-9][0-9]*|0)(\\.)[0-9]{2}"), this));

    QVBoxLayout* layout = new QVBoxLayout();

    QPushButton* enterInTable = new QPushButton("Ввести в таблицу"),
               * mathButton = new QPushButton("Вычислить значения средних пробегов"),
               * deleteElementTable = new QPushButton("Удалить строку таблицы");

    layout->addLayout(hlayout);
    layout->addWidget(ui->tableWidget);
    for(int i = 0; i < dek_size; i++)
        layout->addLayout(&lb_layout[i]);
    layout->addWidget(enterInTable);
    layout->addWidget(mathButton);
    layout->addWidget(deleteElementTable);


    connect(window[0], SIGNAL(clicked()), SLOT(ClickedMainWindow()));
    connect(window[1], SIGNAL(clicked()), SLOT(ClickedPictureWindow()));
    connect(enterInTable, SIGNAL(clicked()), SLOT(ClickedTableButton()));
    connect(mathButton, SIGNAL(clicked()), SLOT(ClickedCalculatorButton()));
    connect(deleteElementTable, SIGNAL(clicked()), SLOT(ClickedDeleteButton()));

    setLayout(layout);
}

TableWidget::~TableWidget()
{
    delete ui;
}

void TableWidget::ClickedMainWindow(){
    this->close();
    emit WindowTable_InMainWindow();
}

void TableWidget::ClickedPictureWindow(){
    this->close();
    emit WindowTable_InPictureWindow();
}

void TableWidget::OpenTableWindow(){
    this->show();
}

void TableWidget::ClickedTableButton(){
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
    for(int i = 0; i < (ui->tableWidget->columnCount()-1); i++){
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setText(inputTableButton[i].text());
        inputTableButton[i].setText("");
        item->setTextAlignment(Qt::AlignCenter | Qt::AlignHCenter);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, i, item);
    }
}

void TableWidget::ClickedDeleteButton(){
    if(ui->tableWidget->rowCount() <= 0)
        return;
    for(int i = 0; i < (ui->tableWidget->columnCount()-1); i++)
        delete ui->tableWidget->item(ui->tableWidget->rowCount()-1, i);
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()-1);
}

void TableWidget::ClickedCalculatorButton(){
    if(ui->tableWidget->rowCount() <= 0)
        return;
    for(int i = 0, j = 3; i < ui->tableWidget->rowCount(); i++){
        double a = ui->tableWidget->item(i, j)->text().toDouble();
        double b = ui->tableWidget->item(i, (j+1))->text().toDouble();
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setText((a)? QString::number((b/a)) : " ");
        ui->tableWidget->setItem(i, (j+2), item);
    }
}
