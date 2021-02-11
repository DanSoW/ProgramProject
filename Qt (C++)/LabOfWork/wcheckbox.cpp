#include "wcheckbox.h"

WCheckBox::WCheckBox(QWidget *parent) : QWidget(parent){
    resize(400, 400);

    QString name_books[count_book] = {QString("\"Война и Мир\""), QString("\"Идиот\""),
                                       QString("\"Преступление и наказание\""),
                                       QString("\"Воскресенье\"")};

    books = new QCheckBox*[count_book];
    for(short i = 0; i < count_book; i++)
        books[i] = new QCheckBox(name_books[i]);
    (*books[0]).setChecked(true);

    QVBoxLayout* layout = new QVBoxLayout();
    for(short i = 0; i < count_book; i++)
        layout->addWidget(books[i]);

    QPushButton* button = new QPushButton("Выбрать книгу");
    (*button).setStyleSheet("background-color: #4d4d4d; text-align: center;"
                            "height: 50px; width: 100px; color: white;");
    connect(button, SIGNAL(clicked()), SLOT(ClickedButton()));

    QGroupBox* group = new QGroupBox("Выбор книги");
    (*group).setLayout(layout);

    main_layout = new QVBoxLayout();
    (*main_layout).addWidget(group);
    (*main_layout).addWidget(button);

    setLayout(main_layout);
}

WCheckBox::~WCheckBox(){
    if(books != nullptr){
        for(short i = 0; i < count_book; i++)
            delete books[i];
        delete[] books;
    }
}
void WCheckBox::ClickedButton(){
    QString change_books = " ";
    for(short i = 0; (i < count_book); i++)
        if(books[i]->isChecked())
            change_books += books[i]->text() + ", ";
    change_books[change_books.size() - 2] = ' ';

    QMessageBox message;
    message.setWindowTitle("Выбор книги");
    message.setStyleSheet("text-align: center;");
    message.setText("Вы выбрали: " + change_books);

    message.exec();
}

QVBoxLayout* WCheckBox::getLayout(){
    return main_layout;
}
