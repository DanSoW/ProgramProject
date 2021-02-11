#ifndef TABLEWINDOW_H
#define TABLEWINDOW_H

#include <QWidget>

namespace Ui {
class TableWindow;
}

class TableWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TableWindow(QWidget *parent = nullptr);
    ~TableWindow();

private:
    Ui::TableWindow *ui;

};

#endif // TABLEWINDOW_H
