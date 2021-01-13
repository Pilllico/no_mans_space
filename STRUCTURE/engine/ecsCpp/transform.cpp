#include "transform.h"

Transform::Transform()
{
    this->position = btVector3(0.0f, 0.0f, 0.0f);
    this->rotation = btVector3(0.0f, 0.0f, 0.0f);
    this->scale = btVector3(1.0f, 1.0f, 1.0f);
}

Transform::Transform(btVector3 pos) : Transform()
{
    this->position = pos;
}

Transform::Transform(btVector3 pos, btVector3 rot) : Transform()
{
    this->position = pos;
    this->rotation = rot;
}

Transform::Transform(btVector3 pos, btVector3 rot, btVector3 scale) : Transform()
{
    this->position = pos;
    this->rotation = rot;
    this->scale = scale;
}

bitmap Transform::getBitMap() const
{
    return componentSignature;
}

btMatrix3x3 Transform::getRotation() const
{
	btMatrix3x3 mat;
	mat.setEulerZYX(rotation.getZ(), rotation.getY(), rotation.getX());
	return mat;
}

Transform::~Transform()
{
    if (motionState != nullptr)
        delete motionState;
}

void MotionState::getWorldTransform(btTransform& worldTrans) const
{
    worldTrans.setOrigin(transform->position);
    worldTrans.setRotation(btQuaternion(transform->rotation.x(), transform->rotation.y(), transform->rotation.z()));
}

void MotionState::setWorldTransform(const btTransform& worldTrans)
{
    //std::cout << "setting origin" << std::endl;
    transform->position = worldTrans.getOrigin();
    btScalar yawZ, pitchY, rollX;
    worldTrans.getRotation().getEulerZYX(yawZ, pitchY, rollX);
    transform->rotation = btVector3(rollX, pitchY, yawZ);
}
