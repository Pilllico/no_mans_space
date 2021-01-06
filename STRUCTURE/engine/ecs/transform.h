#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "component.h"
#include <QVector3D>
#include "motionstate.h"

class Transform : public Component
{
public:
    Transform();
    Transform(QVector3D pos);
    Transform(QVector3D pos, QVector3D rot);
    Transform(QVector3D pos, QVector3D rot, QVector3D scale);
    virtual ~Transform();

    virtual bitmap getBitMap() const;
    static bitmap componentSignature;
    MotionState* motionState = nullptr;

    QVector3D position;
    QVector3D rotation;
    QVector3D scale;
};

#endif // TRANSFORM_H
