#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->setVisible(false);
    ui->stopButton->setEnabled(false);
    setTimeLeft(minutes * 60000);

    connect(ui->startButton, SIGNAL(released()), this, SLOT(start()));
    connect(ui->stopButton, SIGNAL(released()), this, SLOT(stop()));
    connect(&updateTimer, SIGNAL(timeout()), this, SLOT(update()));
}

void MainWindow::start()
{
    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(true);

    endTime = QTime::currentTime().addSecs(minutes * 60);
    updateTimer.start(updateInterval);
}

void MainWindow::stop()
{
    ui->startButton->setEnabled(true);
    ui->stopButton->setEnabled(false);

    updateTimer.stop();

    setTimeLeft(minutes * 60000);
}

void MainWindow::update()
{
    int timeLeftInMs = QTime::currentTime().msecsTo(endTime);

    if (timeLeftInMs >= 0)
    {
        setTimeLeft(timeLeftInMs);
    }
}

void MainWindow::setTimeLeft(int timeLeftInMs)
{
    int minutes = (timeLeftInMs / 1000) / 60;
    int seconds = (timeLeftInMs / 1000) % 60;

    QString labelText = QString("%1:%2").arg(QString::number(minutes), QString::number(seconds).rightJustified(2, '0'));
    ui->clock->setText(labelText);
}

MainWindow::~MainWindow()
{
    delete ui;
}
