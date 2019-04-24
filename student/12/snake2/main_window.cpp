/*
####################################################################
# TIE-02201 Ohjelmointi 2: Perusteet, K2019                        #
# TIE-02207 Programming 2: Basics, S2019                           #
#                                                                  #
# Project4: Snake: The Revengeance                                 #
# Program description: "While revenge is served cold and vengeance #
#                       is served hot revengeance is often seen    #
#                       served with Cajun with a side of onion     #
#                       rings and often dumplings in the Orient."  #
#                       - urbandictionary                          #
#                                                                  #
# File: main_window.cpp                                            #
# Description: Defines a class implementing a UI for the game.     #
#                                                                  #
# Author: Valtteri Kirsilä, 255342, valtteri.kirsila@tuni.fi       #
####################################################################
*/

#include "main_window.hh"
#include "main_window.hh"
#include "main_window.hh"
#include "main_window.hh"
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <ui_main_window.h>
#include <iostream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent):
    QMainWindow(parent),
    ui_(new Ui::MainWindow){

    ui_->setupUi(this);
    ui_->spinBoxDifficulty->setMinimum(1);
    ui_->spinBoxDifficulty->setMaximum(10);
    ui_->spinBoxSize->setMinimum(1);
    ui_->spinBoxSize->setMaximum(10);
    ui_->graphicsView->setScene(&scene_);

    connect(&timer_, &QTimer::timeout, this, &MainWindow::moveSnake);
    connect(&timer2_, &QTimer::timeout, this, &MainWindow::timer);
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    if (hasMoved){
        if (event->key() == Qt::Key_W && yDir != 1){
            xDir = 0;
            yDir = -1;
            hasMoved = false;
        } if (event->key() == Qt::Key_S && yDir != -1){
            xDir = 0;
            yDir = 1;
            hasMoved = false;
        } if (event->key() == Qt::Key_A && xDir != 1){
            xDir = -1;
            yDir = 0;
            hasMoved = false;
        } if (event->key() == Qt::Key_D && xDir != -1){
            xDir = 1;
            yDir = 0;
            hasMoved = false;
        }
    }
}

void MainWindow::on_playButton_clicked() {
    // EXAMPLE: How to create new graphics items in the scene.
    size = ui_->spinBoxSize->value()*10;
    const QRectF head_rect(0, 0, 1, 1);
    const QRectF food_rect(0, 0, 1, 1);
    const QPen pen(Qt::white, 0);
    const QBrush brush2(Qt::darkGreen);
    const QBrush brush(Qt::black);
    snake_ = scene_.addRect(head_rect, pen, brush2);
    snake_->setPos(0, 0);
    food_ = scene_.addRect(food_rect, pen, brush);
    food_->setPos(9, 5);
    xDir = 1;
    adjustSceneArea();
    timer_.start(1000/ui_->spinBoxDifficulty->value());
    ui_->lcdNumberTime->display(0);
    ui_->lcdNumberScore->display(0);
    timer2_.start(1000);
}

void MainWindow::timer(){
    time += 1;
    ui_->lcdNumberTime->display(time);
}

void MainWindow::grow(){
    const QRectF snake_rect(0, 0, 1, 1);
    const QBrush brush3(Qt::green);
    const QPen pen(Qt::white, 0);
    tail_ = scene_.addRect(snake_rect, pen, brush3);
    tail_->setPos(snake_->pos());
    tailList.prepend(tail_);
}

void MainWindow::moveTail(QPointF oldHeadPos){
    if(tailList.size() == 0){
        return;
    } if(tailList.size() == 1){
        tailList[0]->setPos(oldHeadPos);
    } else {
    for (int i = 0; i < tailList.size()-1; i++){
        tailList[i]->setPos(tailList[i+1]->pos());
    }
    tailList.last()->setPos(oldHeadPos);
    }
}

void MainWindow::moveSnake() {
    // EXAMPLE: How to move a graphics item left in the scene.
    const QPointF oldHeadPos = snake_->scenePos();
    if (snake_->x() == 0 && xDir == -1){
        const QPointF newHeadPos = oldHeadPos + QPoint(size-1, yDir);
        snake_->setPos(newHeadPos);
    } else if((snake_->x() == size-1 && xDir == 1)){
        const QPointF newHeadPos = oldHeadPos + QPoint(-size+1, yDir);
        snake_->setPos(newHeadPos);
    } else if((snake_->y() == 0 && yDir == -1)){
        const QPointF newHeadPos = oldHeadPos + QPoint(xDir, size-1);
        snake_->setPos(newHeadPos);
    } else if((snake_->y() == size-1 && yDir == 1)){
        const QPointF newHeadPos = oldHeadPos + QPoint(xDir, -size+1);
        snake_->setPos(newHeadPos);
    } else {
        const QPointF newHeadPos = oldHeadPos + QPoint(xDir, yDir);
        snake_->setPos(newHeadPos);
    }
    if (snake_->pos() == food_->pos()){
        food_->setPos(rand()%size,rand()%size);
        score ++;
        grow();
        ui_->lcdNumberScore->display(score);
    } else if (tailList.size() > 0){
        for(int i = 0; i < tailList.size()-1; i++){
            if(snake_->pos() == tailList[i]->pos()){
                gameOver();
            }
        }
    }
    moveTail(oldHeadPos);
    hasMoved = true;
}

void MainWindow::gameOver(){
    bool newRecord = false;
    timer_.stop();
    timer2_.stop();
    if(score > highScore){
        highScore = score;
        newRecord = true;
    }
    delete snake_;
    delete food_;
    xDir = 1;
    yDir = 0;
    for(int i = 0; i < tailList.size(); i++){
        scene_.removeItem(tailList[i]);
    }
    tailList.clear();
    ui_->playButton->setText("Play again?");
    ui_->playButton->show();
    if (newRecord){
        QMessageBox::information(this, tr("New record!"), QString("Game over :^( New record: %1 points in %2 seconds!").arg(score).arg(time));
    } else {
        QMessageBox::information(this, tr("Game over!"), QString("Game over :^( You scored %1 points in %2 seconds!").arg(score).arg(time));
    }
    ui_->lcdNumberHighScore->display(highScore);
    score = 0;
    time = 0;
}

void MainWindow::adjustSceneArea() {
    // TODO: Replace the area's size with the play field's actual size.
    const QRectF area(0, 0, size, size);
    scene_.setSceneRect(area);
    ui_->graphicsView->fitInView(area);
}
