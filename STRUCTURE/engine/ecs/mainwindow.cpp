#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "entitymanager.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QOpenGLWidget(parent)
{
    timer.start(12, this);
    Entity e = EntityManager::getInstance().createEntity();
    Transform transform = Transform();
    EntityManager::getInstance().addComponentToEntity(&transform, e);
}

MainWindow::~MainWindow()
{

}

void MainWindow::timerEvent(QTimerEvent *e)
{
    displaySystem.execute();
    update();
}

void MainWindow::paintGL()
{

}
