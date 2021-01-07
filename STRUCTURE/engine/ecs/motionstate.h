#ifndef MOTIONSTATE_H
#define MOTIONSTATE_H

#include "bullet/btBulletDynamicsCommon.h"
#include <QVector3D>

class Transform;

class MotionState : public btMotionState
{
public:
    MotionState(Transform* t);
    virtual void getWorldTransform(btTransform& worldTrans) const;
    virtual void setWorldTransform(const btTransform& worldTrans);
    Transform* transform = nullptr;
    virtual ~MotionState();
};

#endif // MOTIONSTATE_H
