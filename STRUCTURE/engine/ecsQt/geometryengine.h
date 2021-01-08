#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions_3_1>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

enum Type {CubeGeometry, PlaneGeometry, SphereGeometry};

struct VertexData
{
    QVector3D position;
    QVector3D normal;
    QVector2D texCoord;
};

class GeometryEngine : protected QOpenGLFunctions_3_1
{
public:
    GeometryEngine();
    virtual ~GeometryEngine();

    void drawGeometry(QOpenGLShaderProgram *program);
    void initAsCubeGeometry();
    void initAsPlaneGeometry(unsigned int n, float size);
    void initAsPlaneGeometry(unsigned int n, float size, const QString &fileName);
    void initAsSphereGeometry();
    float getSize();
    float getRes();

    QVector<VertexData> vertices;
private:
    int vertexSize;

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;

    Type type;
    float size;
    float res;
};

#endif // GEOMETRYENGINE_H
