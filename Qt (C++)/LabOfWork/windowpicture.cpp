#include "windowpicture.h"

WindowPicture::WindowPicture(QWidget *parent) : QWidget(parent){
    setWindowTitle("Картинка");
    resize(600, 600);

    QPushButton* window[3] = {new QPushButton("Выбор"),
                              new QPushButton("Картинка"),
                              new QPushButton("Таблица")};
    window[1]->setEnabled(false);

    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    for(short i = 0; i < 3; i++)
        hlayout->addWidget(window[i]);

    connect(window[0], SIGNAL(clicked()), SLOT(ClickedMainWindow()));
    connect(window[2], SIGNAL(clicked()), SLOT(ClickedTableWindow()));

    setLayout(hlayout);
    timer = new QTimer();
    timer->setInterval(500);
    timer->start();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(RepaintWindow()));
    min = hour = 0;
}

WindowPicture::~WindowPicture(){
    delete timer;
}

void WindowPicture::paintEvent(QPaintEvent* event){
    static const QPoint hourHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -40)
    };
    static const QPoint minuteHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -70)
    };

    QColor hourColor(127, 0, 127);
    QColor minuteColor(0, 127, 127, 191);

    int side = qMin((width()-100), (height()-100));
    QTime time = QTime(hour, min, 0, 0);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate((width() / 2), (height()/ 2));
    painter.scale(side / 200.0, side / 200.0);
    painter.setPen(Qt::NoPen);
    painter.setBrush(hourColor);

    painter.save();

    painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    painter.drawConvexPolygon(hourHand, 3);
    painter.restore();

    painter.setPen(hourColor);

    for (int i = 0; i < 12; ++i) {
        painter.drawLine(88, 0, 96, 0);
        painter.rotate(30.0);
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(minuteColor);

    painter.save();
    painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
    painter.drawConvexPolygon(minuteHand, 3);
    painter.restore();

    painter.setPen(minuteColor);

    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            painter.drawLine(92, 0, 96, 0);
        painter.rotate(6.0);
    }
}

void WindowPicture::ClickedMainWindow(){
    this->close();
    emit WindowPicture_InMainWindow();
}

void WindowPicture::ClickedTableWindow(){
    this->close();
    emit WindowPicture_InTableWindow();
}

void WindowPicture::OpenPictureWindow(){
    this->show();
    repaint();
}
#include <iostream>
void WindowPicture::RepaintWindow(){
    min++;
    if(min >= 60){
        min = 0;
        hour++;
        if(hour >= 24)
            hour = 0;
    }

    repaint();
}
