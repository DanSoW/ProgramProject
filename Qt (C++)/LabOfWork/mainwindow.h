#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "wcheckbox.h"
#include "wmaskedit.h"
#include "wradiobutton.h"
#include <QTabWidget>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    WCheckBox* wcBox;
    WMaskEdit* wmEdit;
    WRadioButton* wrButton;

    QTabWidget* tabWidget;

public slots:
    void ClickedPictureWindow();
    void ClickedTableWindow();
    void OpenMainWindow();

signals:
    void MainWindow_InPictureWindow();
    void MainWindow_InTableWindow();
};

#endif // MAINWINDOW_H
