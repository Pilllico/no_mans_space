#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "component.h"

enum CollisionShape {Sphere, Box};

struct MaterialProperties
{

};

class Physics : public Component
{
public:
    Physics();
    Physics(float mass);
    Physics(float mass, CollisionShape cs);
    ~Physics();

    virtual bitmap getBitMap() const;

    static bitmap componentSignature;
    float mass;
    CollisionShape collisionShape;
    //MaterialProperties matProp;
};

#endif // PHYSICSCOMPONENT_H
