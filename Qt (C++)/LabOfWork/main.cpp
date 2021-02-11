#include <QtWidgets/qapplication.h>
#include "mainwindow.h"
#include "windowpicture.h"
#include "tablewidget.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    WindowPicture picture_window;
    TableWidget table_window;

    QObject::connect(&picture_window, SIGNAL(WindowPicture_InMainWindow()),
            &window, SLOT(OpenMainWindow()));
    QObject::connect(&picture_window, SIGNAL(WindowPicture_InTableWindow()),
                     &table_window, SLOT(OpenTableWindow()));

    QObject::connect(&table_window, SIGNAL(WindowTable_InMainWindow()),
            &window, SLOT(OpenMainWindow()));
    QObject::connect(&table_window, SIGNAL(WindowTable_InPictureWindow()),
                     &picture_window, SLOT(OpenPictureWindow()));

    QObject::connect(&window, SIGNAL(MainWindow_InPictureWindow()),
            &picture_window, SLOT(OpenPictureWindow()));
    QObject::connect(&window, SIGNAL(MainWindow_InTableWindow()),
                     &table_window, SLOT(OpenTableWindow()));
    window.show();
    return a.exec();
}
