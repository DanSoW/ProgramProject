#ifndef WRADIOBUTTON_H
#define WRADIOBUTTON_H

#include <QWidget>
#include <QRadioButton>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>

class WRadioButton : public QWidget
{
    Q_OBJECT
public:
    explicit WRadioButton(QWidget *parent = nullptr);
    ~WRadioButton();

public:
    static const char count_colors = 4;

    QVBoxLayout* getLayout();

private:
    QRadioButton** colors;
    QVBoxLayout* main_layout;

public slots:
    void ClickedButton();

};

#endif // WRADIOBUTTON_H
