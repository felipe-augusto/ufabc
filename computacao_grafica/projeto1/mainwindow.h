#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include "videosurface.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void signalSendImage(QImage *img);

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;

public slots:
    void openImage();
    void openVideo();
};

#endif // MAINWINDOW_H
