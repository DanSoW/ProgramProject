#ifndef WINDOWFIRSTTASK_H
#define WINDOWFIRSTTASK_H

#include <QMainWindow>
#include "wradiobutton.h"
#include "wcheckbox.h"
#include "wmaskedit.h"
#include <QVBoxLayout>

class WindowFirstTask : public QMainWindow
{
    Q_OBJECT
public:
    explicit WindowFirstTask(QWidget *parent = nullptr);

private:
    WRadioButton* wrButton;
    WCheckBox* wcBox;
    WMaskEdit* wmEdit;
};

#endif // WINDOWFIRSTTASK_H
