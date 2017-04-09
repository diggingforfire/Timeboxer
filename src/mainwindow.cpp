#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent, Qt::Window | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stopButton->setEnabled(false);
    ui->decreaseTimerButton->setEnabled(false);

    setStyleSheet("QMainWindow { background: rgb(52, 163, 215); }");
    ui->clock->setStyleSheet("QLabel { color: white; }");
    ui->startButton->setStyleSheet("QPushButton { color: white; background: rgb(195, 36, 81); } QPushButton:disabled { background: rgb(219, 123, 150); }");
    ui->stopButton->setStyleSheet("QPushButton { color: white; background: rgb(195, 36, 81); } QPushButton:disabled { background: rgb(219, 123, 150); }");
    ui->increaseTimerButton->setStyleSheet("QPushButton { color: black; background: rgb(251, 227, 79); } QPushButton:disabled { background: rgb(249, 244, 164); }");
    ui->decreaseTimerButton->setStyleSheet("QPushButton { color: black; background: rgb(239, 105, 38); } QPushButton:disabled { background: rgb(237, 166, 123); }");

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
        ui->clock->setStyleSheet("QLabel { color: rgb(52, 163, 215); }");

        QTime dieTime= QTime::currentTime().addSecs(5);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

        ui->clock->setStyleSheet("QLabel { color: white; }");

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
    QString labelText = QString("%1:%2").arg(QString::number(minutes).rightJustified(2, '0'), QString::number(seconds).rightJustified(2, '0'));
    ui->clock->setText(labelText);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
