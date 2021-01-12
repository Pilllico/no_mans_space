#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "component.h"

enum CollisionShape {Sphere, Box, tMesh/*, Convex*/};

struct MaterialProperties
{

};

class Physics : public Component
{
public:
    Physics();
    Physics(float mass);
	Physics(float mass, CollisionShape cs);
	Physics(float mass, float strength, CollisionShape cs);
	Physics(float mass, float strength, CollisionShape cs, bool isController);
	bool isController = false;
    ~Physics();

    virtual bitmap getBitMap() const;

    static bitmap componentSignature;
    float mass;
	float gravityStrength;
    CollisionShape collisionShape;
    //MaterialProperties matProp;
};

#endif // PHYSICSCOMPONENT_H
