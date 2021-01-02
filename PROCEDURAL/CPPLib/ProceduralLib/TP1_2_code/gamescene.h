#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "gameobject.h"
#include "gameterrainobject.h"
#include "gamecubeobject.h"
#include "gameearthobject.h"
#include "gamesunobject.h"
#include "gamemoonobject.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_1>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

using namespace std;

class GameObject;

class GameScene : public QOpenGLWidget, protected QOpenGLFunctions_3_1{

    Q_OBJECT

    public:
        explicit GameScene(QWidget *parent = 0);
        ~GameScene();

         void addObject(GameObject* obj){gameObject->addChild(obj);}

    protected:
        void keyPressEvent(QKeyEvent *e) override;
        void mousePressEvent(QMouseEvent *e) override;
        void mouseReleaseEvent(QMouseEvent *e) override;
        void timerEvent(QTimerEvent *e) override;

        void updateScene();
        void initializeGL() override;
        void resizeGL(int w, int h) override;
        void paintGL() override;

        void initShaders();
        void initTextures();

    private:
        QBasicTimer timer;
        QOpenGLShaderProgram program;
        GameObject* gameObject;

        QOpenGLTexture *textureGrass;
        QOpenGLTexture *textureRock;
        QOpenGLTexture *textureSnow;
        QOpenGLTexture *textureMap;

        QMatrix4x4 projection;

        QVector2D mousePressPosition;
        QVector3D rotationAxis;
        qreal angularSpeed;
        QQuaternion rotation;

        float xOffset,yOffset,zOffset;
        bool freeView = true;
};

#endif // GAMESCENE_H
