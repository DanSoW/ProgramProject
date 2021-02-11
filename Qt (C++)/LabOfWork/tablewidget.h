#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QLineEdit>

namespace Ui {
class TableWidget;
}

class TableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TableWidget(QWidget *parent = nullptr);
    ~TableWidget();

private:
    Ui::TableWidget *ui;
    QLineEdit* inputTableButton;
    const char count_column = 6;

signals:
    void WindowTable_InMainWindow();
    void WindowTable_InPictureWindow();

public slots:
    void ClickedPictureWindow();
    void ClickedMainWindow();
    void OpenTableWindow();
    void ClickedTableButton();
    void ClickedDeleteButton();
    void ClickedCalculatorButton();
};

#endif // TABLEWIDGET_H
