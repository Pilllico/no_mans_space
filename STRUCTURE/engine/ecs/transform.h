#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "component.h"
#include <QVector3D>

class Transform : public Component
{
public:
    Transform();
    Transform(QVector3D pos);
    Transform(QVector3D pos, QVector3D rot);
    Transform(QVector3D pos, QVector3D rot, QVector3D scale);
    const QVector3D& getPosition() const;
    const QVector3D& getRotation() const;
    const QVector3D& getScale() const;
    virtual bitmap getBitMap();
    virtual ~Transform();

    static bitmap componentSignature;
private:    
    QVector3D position;
    QVector3D rotation;
    QVector3D scale;
};

#endif // TRANSFORM_H
