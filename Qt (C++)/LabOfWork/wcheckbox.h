#ifndef WCHECKBOX_H
#define WCHECKBOX_H

#include <QWidget>
#include <QRadioButton>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QCheckBox>

class WCheckBox : public QWidget
{
    Q_OBJECT
public:
    explicit WCheckBox(QWidget *parent = nullptr);
    ~WCheckBox();

public:
    static const char count_book = 4;

    QVBoxLayout* getLayout();
private:
    QCheckBox** books;
    QVBoxLayout* main_layout;

public slots:
    void ClickedButton();

};

#endif // WCHECKBOX_H
