#include "rendersystem.h"

renderSystem::renderSystem()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();

    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);

    sphere = new GeometryEngine();
    sphere->initAsSphereGeometry();
    cube = new GeometryEngine();
    cube->initAsCubeGeometry();
}

renderSystem::~renderSystem()
{
    delete sphere;
    delete cube;
}

bool renderSystem::initShaders()
{
    if (!basicProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vbasicShader.glsl"))
        return false;

    if (!basicProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fbasicShader.glsl"))
        return false;

    if (!basicProgram.link())
        return false;
    return true;
}

void renderSystem::resizeWindows(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 1, zFar = 100.0, fov = 45.0;

    // Reset projection
    Projection.setToIdentity();

    // Set perspective projection
    Projection.perspective(fov, static_cast<float>(aspect), zNear, zFar);
}

bool renderSystem::execute()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!basicProgram.bind())
            return false;

    View.setToIdentity();
    View.lookAt(QVector3D(0.0f, 5.0f, 10.0f), QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f));

    TransformManager* transformManager = dynamic_cast<TransformManager*>(EntityManager::getInstance().getComponentManagerForSystem(bitmap("1")));
    const std::unordered_map<Entity, Transform, EntityHasher>& transforms = transformManager->getAllTransforms();

    basicProgram.setUniformValue("view_matrix", View);
    basicProgram.setUniformValue("projection_matrix", Projection);

    basicProgram.setUniformValue("lightPos", QVector3D(0.0f, 0.0f, 15.0f));

    int i = 0;
    for (auto & pair : transforms) {
        QMatrix4x4 obj_model;
        obj_model.setToIdentity();
        obj_model.translate(pair.second.position);
        obj_model.rotate(QQuaternion::fromEulerAngles(pair.second.rotation));
        obj_model.scale(pair.second.scale);

        basicProgram.setUniformValue("model_matrix", obj_model);

        if (i==0)
            cube->drawGeometry(&basicProgram);
        else
            sphere->drawGeometry(&basicProgram);
        i++;
    }
    return true;
}
