#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "system.h"
#include "geometryengine.h"

#include <QOpenGLFunctions_3_1>
#include <QOpenGLShaderProgram>

class renderSystem : public System, protected QOpenGLFunctions_3_1
{
public:
    renderSystem();
    bool virtual execute();
    void resizeWindows(int w, int h);
    bool initShaders();
    ~renderSystem();
private:
     QOpenGLShaderProgram basicProgram;

     QMatrix4x4 Model;
     QMatrix4x4 View;
     QMatrix4x4 Projection;

     GeometryEngine* sphere;
     GeometryEngine* cube;
};

#endif // RENDERSYSTEM_H
