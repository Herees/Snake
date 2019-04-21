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

MainWindow::MainWindow(QWidget* parent):
    QMainWindow(parent) {

    ui_.setupUi(this);
    ui_.graphicsView->setScene(&scene_);

    connect(&timer_, &QTimer::timeout, this, &MainWindow::moveSnake);
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    // Move up
    if (event->key() == Qt::Key_W){
        xDir = 0;
        yDir = -1;
    } if (event->key() == Qt::Key_S){
        xDir = 0;
        yDir = 1;
    } if (event->key() == Qt::Key_A){
        xDir = -1;
        yDir = 0;
    } if (event->key() == Qt::Key_D){
        xDir = 1;
        yDir = 0;
    }

}

void MainWindow::on_playButton_clicked() {
    // EXAMPLE: How to create new graphics items in the scene.
    const QRectF snake_rect(0, 0, 1, 1);
    const QRectF food_rect(0, 0, 1, 1);
    const QPen pen(Qt::white, 0);
    const QBrush brush2(Qt::green);
    const QBrush brush(Qt::black);
    snake_ = scene_.addRect(snake_rect, pen, brush2);
    snake_->setPos(0, 0);
    food_ = scene_.addRect(food_rect, pen, brush);
    food_->setPos(9, 5);
    xDir = 1;

    adjustSceneArea();
    timer_.start(1000);
}

void MainWindow::grow(QPointF oldHeadPos){
    const QRectF snake_rect(0, 0, 1, 1);
    const QBrush brush3(Qt::darkGreen);
    const QPen pen(Qt::white, 0);
    tail_ = scene_.addRect(snake_rect, pen, brush3);
    tail_->setPos(oldHeadPos);
    tailList.append(tail_);
    moveSnake();
}

void MainWindow::moveTail(QPointF oldHeadPos){
    for (size_t i = 0; i < tailList.size()-1; i++){
        tailList[i]->setPos(tailList[i+1]->pos());
    }
    tailList.last()->setPos(oldHeadPos);
}

void MainWindow::moveSnake() {
    // EXAMPLE: How to move a graphics item left in the scene.
    const QPointF oldHeadPos = snake_->scenePos();
    const QPointF newHeadPos = oldHeadPos + QPoint(xDir, yDir);
    snake_->setPos(newHeadPos);
    if (tailList.size() > 0){
        moveTail(oldHeadPos);
    }
    if (snake_->pos() == food_->pos()){
            food_->setPos(rand()%10,rand()%10);
            grow(oldHeadPos);
}
}

void MainWindow::adjustSceneArea() {
    // TODO: Replace the area's size with the play field's actual size.
    const QRectF area(0, 0, 10, 10);
    scene_.setSceneRect(area);
    ui_.graphicsView->fitInView(area);
}
