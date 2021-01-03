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

const QVector3D& Transform::getPosition() const
{
    return this->position;
}

const QVector3D& Transform::getRotation() const
{
    return this->rotation;
}

const QVector3D& Transform::getScale() const
{
    return this->scale;
}

bitmap Transform::getBitMap() const {
    return componentSignature;
}

Transform::~Transform()
{

}
