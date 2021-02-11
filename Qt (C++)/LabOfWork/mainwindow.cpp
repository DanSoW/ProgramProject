#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent){
    setWindowTitle("Выбор");
    resize(600, 600);

    QPushButton* window[3] = {new QPushButton("Выбор"),
                              new QPushButton("Картинка"),
                              new QPushButton("Таблица")};
    window[0]->setEnabled(false);

    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    for(short i = 0; i < 3; i++)
        hlayout->addWidget(window[i]);

    wcBox = new WCheckBox();
    wrButton = new WRadioButton();
    wmEdit = new WMaskEdit();

    tabWidget = new QTabWidget();
    tabWidget->addTab(wrButton, "Переключатели");
    tabWidget->addTab(wcBox, "Флажки");
    tabWidget->addTab(wmEdit, "Ввод данных");

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addLayout(hlayout);
    layout->addWidget(tabWidget);

    setLayout(layout);
    show();

    connect(window[1], SIGNAL(clicked()), SLOT(ClickedPictureWindow()));
    connect(window[2], SIGNAL(clicked()), SLOT(ClickedTableWindow()));
}

void MainWindow::OpenMainWindow(){
    this->show();
}

void MainWindow::ClickedTableWindow(){
    this->close();
    emit MainWindow_InTableWindow();
}

void MainWindow::ClickedPictureWindow(){
    this->close();
    emit MainWindow_InPictureWindow();
}
