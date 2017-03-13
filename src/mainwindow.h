#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDateTime>

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
    void decreaseTimer();
    void increaseTimer();

private:
    Ui::MainWindow *ui;
    QTimer updateTimer;
    QDateTime endTime;
    const int minMinutes = 5;
    const int maxMinutes = 60;
    const int stepSize = 5;
    int currentMinutes = 5;
    const int updateInterval = 100; // most certainly overkill but whatever
    void setTimeLeftText(int minutes, int seconds);
    void setEndTime();
};

#endif // MAINWINDOW_H
