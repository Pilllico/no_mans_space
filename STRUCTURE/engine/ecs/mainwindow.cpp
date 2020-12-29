#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "entitymanager.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QOpenGLWidget(parent)
{
    timer.start(12, this);
    Entity e1 = EntityManager::getInstance().createEntity();
    Entity e2 = EntityManager::getInstance().createEntity();
    Transform transform1 = Transform();
    Transform transform2 = Transform(QVector3D(10.0f, 0.0f, -5.0f));
    EntityManager::getInstance().addComponentToEntity(&transform1, e1);
    EntityManager::getInstance().addComponentToEntity(&transform2, e2);
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
