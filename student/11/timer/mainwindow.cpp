#include "mainwindow.hh"
#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    min = 0;
    sec = 0;
    timer = new QTimer(this);
    ui->setupUi(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(seconds2minutes()));
    connect(ui->startButton, SIGNAL (clicked()), this, SLOT (start()));
    connect(ui->resetButton, SIGNAL (clicked()), this, SLOT (reset()));
    connect(ui->closeButton, SIGNAL (clicked()), this, SLOT (stop()));
}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui;
}

void MainWindow::start(){
    timer->start(1000);
}

void MainWindow::seconds2minutes(){
    sec += 1;
if(sec > 60){
    sec -= 60;
    min +=1;
}
ui->lcdNumberMin->display(min);
ui->lcdNumberSec->display(sec);
}

void MainWindow::reset(){
    sec = 0;
    min = 0;
    ui->lcdNumberMin->display(min);
    ui->lcdNumberSec->display(sec);
    timer->stop();
}

void MainWindow::stop(){
    close();
}
