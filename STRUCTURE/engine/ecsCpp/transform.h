#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "bullet/LinearMath/btVector3.h"
#include "component.h"
#include "motionstate.h"

class Transform : public Component
{
public:
    Transform();
    Transform(btVector3 pos);
    Transform(btVector3 pos, btVector3 rot);
    Transform(btVector3 pos, btVector3 rot, btVector3 scale);
    virtual ~Transform();

    virtual bitmap getBitMap() const;
    static bitmap componentSignature;
    MotionState* motionState = nullptr;

	btVector3 position;
	btVector3 rotation;
	btVector3 scale;
};

#endif // TRANSFORM_H
