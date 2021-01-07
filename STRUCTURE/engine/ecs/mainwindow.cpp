#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "entitymanager.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QOpenGLWidget(parent)
{
    timer.start(16, this);
    Entity e1 = EntityManager::getInstance().createEntity();
    Entity e2 = EntityManager::getInstance().createEntity();

    EntityManager::getInstance().addComponentToEntity(e1, QVector3D(0.0f, 5.0f, 0.0f), QVector3D(0.0f, 0.0f, 0.0f), QVector3D(1.0f, 1.0f, 1.0f));
    EntityManager::getInstance().addComponentToEntity(e2, QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 0.0f, 0.0f), QVector3D(1.0f, 1.0f, 1.0f));
    EntityManager::getInstance().addComponentToEntity(e1, 1.0f, Sphere);
    EntityManager::getInstance().addComponentToEntity(e2, 0.0f, Box);
}

MainWindow::~MainWindow()
{

}

void MainWindow::timerEvent(QTimerEvent *e)
{
    displaySystem.execute();
    physicsSystem.execute();
}

void MainWindow::paintGL()
{

}
