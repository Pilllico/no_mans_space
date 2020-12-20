#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "component.h"
#include <QVector3D>

class Transform : public Component
{
public:
    Transform();
    std::bitset<16> getBitset();
private:
    QVector3D position;
    QVector3D rotation;
    QVector3D scale;
};

#endif // TRANSFORM_H
