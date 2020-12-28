#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_1>
#include <QBasicTimer>

#include "displaysystem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QOpenGLWidget, protected QOpenGLFunctions_3_1
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void timerEvent(QTimerEvent *e) override;
    void paintGL() override;
private:
    displaySystem displaySystem;
    QBasicTimer timer;
};
#endif // MAINWINDOW_H
