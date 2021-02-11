#ifndef WINDOWPICTURE_H
#define WINDOWPICTURE_H

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QTimer>
#include <QTime>

class WindowPicture : public QWidget
{
    Q_OBJECT
public:
    explicit WindowPicture(QWidget *parent = nullptr);
    ~WindowPicture();

private:
    QTimer* timer;
    int min;
    int hour;

protected:
    void paintEvent(QPaintEvent*);

signals:
    void WindowPicture_InTableWindow();
    void WindowPicture_InMainWindow();

public slots:
    void ClickedTableWindow();
    void ClickedMainWindow();
    void OpenPictureWindow();
    void RepaintWindow();
};

#endif // WINDOWPICTURE_H
