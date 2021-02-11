#include "windowfirsttask.h"

WindowFirstTask::WindowFirstTask(QWidget *parent) : QMainWindow(parent){
    setWindowTitle("Лабораторная работа №6");

    QHBoxLayout* layout = new QHBoxLayout();

    wrButton = new WRadioButton();
    wcBox = new WCheckBox();
    wmEdit = new WMaskEdit();

    layout->addWidget(wrButton);
    layout->addWidget(wcBox);
    layout->addWidget(wmEdit);

}
