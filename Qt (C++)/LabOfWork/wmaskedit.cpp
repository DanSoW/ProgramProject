#include "wmaskedit.h"
#include <QDoubleValidator>

WMaskEdit::WMaskEdit(QWidget *parent) : QWidget(parent){
    resize(400, 400);
    line1 = new QLineEdit();
    line2 = new QLineEdit();

    QLabel* lab1 = new QLabel("Введите стоимость квадратного метра: "),
            *lab2 = new QLabel("Введите метраж квартиры (м в квадрате): ");

    lab1->setStyleSheet("margin-right: 20px;");
    lab2->setStyleSheet("margin-right: 5px;");
    line1->setStyleSheet("margin-right: 200px;");
    line2->setStyleSheet("margin-right: 200px;");

    QHBoxLayout* hlayout1 = new QHBoxLayout(),
            *hlayout2 = new QHBoxLayout();
    main_layout = new QVBoxLayout();


    QPushButton* button = new QPushButton("Рассчёт суммы оплаты");
    (*button).setStyleSheet("background-color: #4d4d4d; text-align: center;"
                            "height: 50px; width: 100px; color: white;");

    connect(button, SIGNAL(clicked()), SLOT(ClickedButton()));

    hlayout1->setMargin(10);
    hlayout1->setSpacing(5);
    hlayout2->setMargin(10);
    hlayout2->setSpacing(5);

    hlayout1->addWidget(lab1);
    hlayout1->addWidget(line1);

    hlayout2->addWidget(lab2);
    hlayout2->addWidget(line2);

    main_layout->addLayout(hlayout1);
    main_layout->addLayout(hlayout2);
    main_layout->addWidget(button);

    setLayout(main_layout);

    line1->setValidator(new QRegExpValidator(QRegExp("^([1-9][0-9]*|0)(\\.)[0-9]{2}"), this));
    line2->setValidator(new QRegExpValidator(QRegExp("^([1-9][0-9]*|0)(\\.)[0-9]{2}"), this));
}

void WMaskEdit::ClickedButton(){
    double sum = (line1->text().toDouble() * line2->text().toDouble());
    QMessageBox message;
    message.setWindowTitle("Подсчёт суммы оплаты");
    message.setStyleSheet("text-align: center;");
    message.setText("Сумма оплаты: " + QString::number((double)sum));
    message.exec();
}

QVBoxLayout* WMaskEdit::getLayout(){
    return main_layout;
}
