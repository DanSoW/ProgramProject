#ifndef WMASKEDIT_H
#define WMASKEDIT_H

#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>

class WMaskEdit : public QWidget
{
    Q_OBJECT
public:
    explicit WMaskEdit(QWidget *parent = nullptr);

public:
    QVBoxLayout* getLayout();

private:
    QLineEdit* line1;
    QLineEdit* line2;
    QVBoxLayout* main_layout;

public slots:
    void ClickedButton();
};

#endif // WMASKEDIT_H
