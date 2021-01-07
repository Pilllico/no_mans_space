#include "transform.h"

Transform::Transform()
{
    this->position = QVector3D(0.0f, 0.0f, 0.0f);
    this->rotation = QVector3D(0.0f, 0.0f, 0.0f);
    this->scale = QVector3D(1.0f, 1.0f, 1.0f);
}

Transform::Transform(QVector3D pos) : Transform()
{
    this->position = pos;
}

Transform::Transform(QVector3D pos, QVector3D rot) : Transform()
{
    this->position = pos;
    this->rotation = rot;
}

Transform::Transform(QVector3D pos, QVector3D rot, QVector3D scale) : Transform()
{
    this->position = pos;
    this->rotation = rot;
    this->scale = scale;
}

bitmap Transform::getBitMap() const
{
    return componentSignature;
}

Transform::~Transform()
{
    if (motionState != nullptr)
        delete motionState;
}

void MotionState::getWorldTransform(btTransform& worldTrans) const
{
    btVector3 position = btVector3(transform->position.x(), transform->position.y(), transform->position.z());
    btVector3 rot = btVector3(transform->rotation.x(), transform->rotation.y(), transform->rotation.z());

    //std::cout << "getting origin" << std::endl;

    worldTrans.setOrigin(position);
    //worldTrans.setRotation();
}

void MotionState::setWorldTransform(const btTransform& worldTrans)
{
    //std::cout << "setting origin" << std::endl;
    transform->position = QVector3D(worldTrans.getOrigin().getX(), worldTrans.getOrigin().getY(), worldTrans.getOrigin().getZ());
}
