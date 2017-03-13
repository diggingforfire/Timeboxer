#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->setVisible(false);
    ui->stopButton->setEnabled(false);
    ui->decreaseTimerButton->setEnabled(false);

    connect(ui->startButton, SIGNAL(released()), this, SLOT(start()));
    connect(ui->stopButton, SIGNAL(released()), this, SLOT(stop()));
    connect(ui->increaseTimerButton, SIGNAL(released()), this, SLOT(increaseTimer()));
    connect(ui->decreaseTimerButton, SIGNAL(released()), this, SLOT(decreaseTimer()));
    connect(&updateTimer, SIGNAL(timeout()), this, SLOT(update()));

    setTimeLeftText(currentMinutes, 0);
}

void MainWindow::start()
{
    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(true);
    ui->decreaseTimerButton->setEnabled(false);
    ui->increaseTimerButton->setEnabled(false);

    setEndTime();
    updateTimer.start(updateInterval);
}

void MainWindow::stop()
{
    updateTimer.stop();

    currentMinutes = minMinutes;

    ui->startButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
    ui->increaseTimerButton->setEnabled(true);

    setTimeLeftText(currentMinutes, 0);
}

void MainWindow::update()
{
    int timeLeftInSeconds = QDateTime::currentDateTime().secsTo(endTime);

    if (timeLeftInSeconds >= 0)
    {
        int minutes = timeLeftInSeconds / 60;
        int seconds = timeLeftInSeconds % 60;

        setTimeLeftText(minutes, seconds);
    }
    else
    {
        ui->clock->setStyleSheet("QLabel { color: red; }");

        QTime dieTime= QTime::currentTime().addSecs(7);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

        ui->clock->setStyleSheet("QLabel { color: black; }");

        stop();
    }
}

void MainWindow::setEndTime()
{
     endTime = QDateTime::currentDateTime().addSecs(currentMinutes * 60);
}

void MainWindow::decreaseTimer()
{
    currentMinutes -= stepSize;
    setTimeLeftText(currentMinutes, 0);

    if (currentMinutes == minMinutes)
    {
        ui->decreaseTimerButton->setEnabled(false);
    }

    ui->increaseTimerButton->setEnabled(true);
}

void MainWindow::increaseTimer()
{
    currentMinutes += stepSize;
    setTimeLeftText(currentMinutes, 0);

    if (currentMinutes == maxMinutes)
    {
        ui->increaseTimerButton->setEnabled(false);
    }

    ui->decreaseTimerButton->setEnabled(true);
}

void MainWindow::setTimeLeftText(int minutes, int seconds)
{
    QString labelText = QString("%1:%2").arg(QString::number(minutes), QString::number(seconds).rightJustified(2, '0'));
    ui->clock->setText(labelText);
}

MainWindow::~MainWindow()
{
    delete ui;
}
