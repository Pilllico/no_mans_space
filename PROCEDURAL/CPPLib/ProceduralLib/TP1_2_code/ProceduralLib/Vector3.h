#ifndef VECTOR3_H
#define VECTOR3_H
class Vector3 {

public:

    float x, y, z;

    Vector3(){}

    Vector3(float x, float y, float z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector3(Vector3 &v){
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
    }

    static Vector3 zero(){
        return *new Vector3();
    }

    static Vector3 one(){
        return *new Vector3(1, 1, 1);
    }

};
#endif // VECTOR3_H
