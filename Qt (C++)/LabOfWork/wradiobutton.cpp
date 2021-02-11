#include "wradiobutton.h"

WRadioButton::WRadioButton(QWidget *parent) : QWidget(parent){
    resize(400, 400);

    QString name_colors[count_colors] = {QString("Красный"), QString("Чёрный"),
                                       QString("Зелёный"),
                                       QString("Синий")};

    colors = new QRadioButton*[count_colors];
    for(short i = 0; i < count_colors; i++)
        colors[i] = new QRadioButton(name_colors[i]);
    (*colors[0]).setChecked(true);

    QVBoxLayout* layout = new QVBoxLayout();
    for(short i = 0; i < count_colors; i++)
        layout->addWidget(colors[i]);

    QPushButton* button = new QPushButton("Выбрать цвет");
    (*button).setStyleSheet("background-color: #4d4d4d; text-align: center;"
                            "height: 50px; width: 100px; color: white;");
    connect(button, SIGNAL(clicked()), SLOT(ClickedButton()));

    QGroupBox* group = new QGroupBox("Выбор цвета");
    (*group).setLayout(layout);

    main_layout = new QVBoxLayout();
    (*main_layout).addWidget(group);
    (*main_layout).addWidget(button);

    setLayout(main_layout);
}

WRadioButton::~WRadioButton(){
    if(colors != nullptr){
        for(short i = 0; i < count_colors; i++)
            delete colors[i];
        delete[] colors;
    }
}
void WRadioButton::ClickedButton(){
    short change = (-1);
    for(short i = 0; (i < count_colors) && (change < 0); i++)
        if(colors[i]->isChecked())
            change = i;
    QString name_colors[count_colors] = {const_cast<char*>("Красный"), const_cast<char*>("Чёрный"),
                                       const_cast<char*>("Зелёный"),
                                       const_cast<char*>("Синий")};
    QString color = name_colors[change];

    QMessageBox message;
    message.setWindowTitle("Выбор цвета");
    message.setStyleSheet("text-align: center;");
    message.setText("Вы выбрали " + color + " цвет");

    message.exec();
}

QVBoxLayout* WRadioButton::getLayout(){
    return main_layout;
}
