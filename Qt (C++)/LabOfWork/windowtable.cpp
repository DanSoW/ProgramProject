#include "windowtable.h"

WindowTable::WindowTable(QWidget *parent) : QWidget(parent){
    setWindowTitle("Таблица");
    resize(600, 600);

    QPushButton* window1 = new QPushButton("Выбор"),
            *window2 = new QPushButton("Картинка"),
            *window3 = new QPushButton("Таблица");
    window3->setEnabled(false);

    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    hlayout->addWidget(window1);
    hlayout->addWidget(window2);
    hlayout->addWidget(window3);

    //марка автомобиля
    //номер
    //вид – грузовой или легковой
    //пробег в километрах
    //число месяцев пробега
    //средний пробег в месяц – вычисляется

    /*QStringList headers;
    headers.push_back("Марка автомобиля");
    headers.push_back("Номер");
    headers.push_back("Вид");
    headers.push_back("Пробег(км)");
    headers.push_back("Число месяцев пробега");
    headers.push_back("Средний пробег в месяц");*/

    //tableWidget = new QTableWidget(); //Количество столбцов
    /*tableWidget->setShowGrid(true); //включаем сетку
    // Разрешаем выделение только одного элемента
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    // Разрешаем выделение построчно
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем заголовки колонок
    tableWidget->setHorizontalHeaderLabels(headers);
    // Растягиваем последнюю колонку на всё доступное пространство
    //tableWidget->horizontalHeader().setStretchLastSection(true);
    // Скрываем колонку под номером 0
    //tableWidget->hideColumn(0);*/

    QVBoxLayout* layout = new QVBoxLayout();

    layout->addLayout(hlayout);


    connect(window1, SIGNAL(clicked()), SLOT(ClickedMainWindow()));
    connect(window2, SIGNAL(clicked()), SLOT(ClickedPictureWindow()));

    setLayout(layout);
}


void WindowTable::ClickedMainWindow(){
    this->close();
    emit WindowTable_InMainWindow();
}

void WindowTable::ClickedPictureWindow(){
    this->close();
    emit WindowTable_InPictureWindow();
}

void WindowTable::OpenTableWindow(){
    this->show();
}
