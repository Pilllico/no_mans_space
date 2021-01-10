#pragma once

#include <math.h>

class Vector3{
public:

    static Vector3 back;
    static Vector3 down;
    static Vector3 forward;
    static Vector3 left;
    static Vector3 right;
    static Vector3 up;
    static Vector3 zero;
    static Vector3 one;

    float x, y, z;

    Vector3() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }

    Vector3(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector3(const Vector3& v) {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
    }

    static Vector3 Cross(Vector3 a, Vector3 b) {
        return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
    }

    static int Dot(Vector3 a, Vector3 b) {
        int product = 0;
        for (int i = 0; i < 3; i++) product = product + a[i] * b[i];
        return product;
    }

    float operator [] (int i) {
        if (i == 0) return this->x;
        if (i == 1) return this->y;
        if (i == 2) return this->z;
        throw "Trying to access invalid member of Vector3";
    }

    Vector3 operator + (Vector3 const& obj) {
        Vector3 res;
        res.x = this->x + obj.x;
        res.y = this->y + obj.y;
        res.z = this->z + obj.z;
        return res;
    }

    Vector3 operator - (Vector3 const& obj) {
        Vector3 res;
        res.x = this->x - obj.x;
        res.y = this->y - obj.y;
        res.z = this->z - obj.z;
        return res;
    }

    Vector3 operator * (float obj) {
        Vector3 res;
        res.x = this->x * obj;
        res.y = this->y * obj;
        res.z = this->z * obj;
        return res;
    }

    Vector3 normalized() {
        float length = sqrt((double)this->x * this->x + this->y * this->y + this->z * this->z);
        return Vector3(this->x / length, this->y / length, this->z / length);
    
    }

};

