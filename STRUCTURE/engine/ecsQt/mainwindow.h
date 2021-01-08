#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "geometryengine.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_1>
#include <QBasicTimer>
//#include <QOpenGLShaderProgram>

#include "displaysystem.h"
#include "physicssystem.h"
#include "rendersystem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QOpenGLWidget, protected QOpenGLFunctions_3_1
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void timerEvent(QTimerEvent *e) override;
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void initShaders();
    void paintGL() override;
private:
    displaySystem displaySystem;
    physicsSystem physicsSystem;
    //renderSystem renderSystem;
    QBasicTimer timer;

    QOpenGLShaderProgram basicProgram;

    QMatrix4x4 Model;
    QMatrix4x4 View;
    QMatrix4x4 Projection;

    GeometryEngine* sphere;
    GeometryEngine* cube;
};
#endif // MAINWINDOW_H
