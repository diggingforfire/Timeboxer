#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void start();
    void stop();
    void update();

private:
    Ui::MainWindow *ui;
    QTimer updateTimer;
    QTime endTime;
    int minutes = 5;
    const int updateInterval = 100; // most certainly overkill but whatever
    void setTimeLeft(int timeLeft);
};

#endif // MAINWINDOW_H
