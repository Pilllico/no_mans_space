#include "gamescene.h"

#include <QMouseEvent>

#include <math.h>

GameScene::GameScene(QWidget *parent) :QOpenGLWidget(parent),gameObject(0),textureGrass(0),textureRock(0),textureSnow(0),textureMap(0),angularSpeed(0){
    xOffset = 0;
    yOffset = -1;
    zOffset = 0;

}

GameScene::~GameScene(){
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete gameObject;
    doneCurrent();
}

void GameScene::keyPressEvent(QKeyEvent *e){
    if(freeView){
        if(e->key() == Qt::Key_W){zOffset+=0.1;}
        if(e->key() == Qt::Key_S){zOffset-=0.1;}
        if(e->key() == Qt::Key_A){xOffset+=0.1;}
        if(e->key() == Qt::Key_D){xOffset-=0.1;}
        if(e->key() == Qt::Key_Space){yOffset-=0.1;}
        if(e->key() == Qt::Key_Shift){yOffset+=0.1;}
    }
    if(e->key() == Qt::Key_C){freeView = !freeView;}
    update();
}

void GameScene::mousePressEvent(QMouseEvent *e){
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void GameScene::mouseReleaseEvent(QMouseEvent *e){
    if(freeView){
        // Mouse release position - mouse press position
        QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

        // Rotation axis is perpendicular to the mouse position difference
        // vector
        QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

        // Accelerate angular speed relative to the length of the mouse sweep
        qreal acc = diff.length() / 10.0;

        // Calculate new rotation axis as weighted sum
        rotationAxis = ( rotationAxis * angularSpeed + n * acc).normalized();
        rotationAxis[0] = 0;
        rotationAxis[2] = 0;
        // Increase angular speed
        angularSpeed += acc;
    }
}

void GameScene::timerEvent(QTimerEvent *){
    if(freeView){
        // Decrease angular speed (friction)
        angularSpeed *= 0.70;

        // Stop rotation when speed goes below threshold
        if (angularSpeed < 0.01) {
            angularSpeed = 0.0;
        } else {
            // Update rotation
            rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

            // Request an update

        }
    }else{
        rotation = QQuaternion::fromAxisAndAngle(0,1,0, 0.5) * rotation;
        update();
    }

    updateScene();

}

void GameScene::initializeGL(){
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();


    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    //glEnable(GL_CULL_FACE);

    gameObject = new GameObject;

    //Child1
    GameSunObject* sun = new GameSunObject;
    sun->setTexture(":/sun.png");
    sun->transform.rescale(QVector3D(1.5,1.5,1.5));
    sun->transform.rotateLocal(45, QVector3D(1,1,1));

    GameEarthObject* earth = new GameEarthObject;
    earth->setTexture(":/earth.png");
    earth->transform.rescale(QVector3D(0.5,0.5,0.5));
    earth->transform.translate(QVector3D(10,0,0));
    earth->transform.rotateLocal(23.4, QVector3D(1,0,0));

    GameMoonObject* moon = new GameMoonObject;
    moon->setTexture(":/moon.png");
    moon->transform.rescale(QVector3D(0.3,0.3,0.3));
    moon->transform.translate(QVector3D(10,0,0));
    earth->transform.rotateLocal(6.7, QVector3D(1,0,0));

    earth->addChild(moon);

    sun->addChild(earth);

    gameObject->addChild(sun);

    //Init
    gameObject->init();
    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);
}


void GameScene::initShaders(){
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}


void GameScene::resizeGL(int w, int h){
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 1.0, zFar = 70.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}

void GameScene::updateScene(){
    gameObject->update();
    update();
}

void GameScene::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.1,0.1,0.2,1);

    // Calculate model view transformation
    QMatrix4x4 matrix;
    if(freeView){
        matrix.rotate(rotation);
        matrix.translate(xOffset, yOffset, zOffset);
    }else{


        matrix.rotate( QQuaternion::fromAxisAndAngle(1,0,0,45));

        matrix.rotate(rotation);

        matrix.translate(0, -7, -0);

    }
    // Set modelview-projection matrix
    program.setUniformValue("mvp_matrix", projection * matrix);

    // Use texture unit 0 which contains cube.png
    program.setUniformValue("textureGrass", 0);
    program.setUniformValue("textureRock", 1);
    program.setUniformValue("textureSnow", 2);
    program.setUniformValue("textureMap", 3);

    gameObject->draw(&program);
}
