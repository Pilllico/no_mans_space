#pragma once
class Vector2{
public:
    float x, y;

    Vector2() {
        this->x = 0;
        this->y = 0;
    }

    Vector2(float x, float y) {
        this->x = x;
        this->y = y;
    }

    Vector2(const Vector2& v) {
        this->x = v.x;
        this->y = v.y;
    }

    static Vector2 zero() {
        return *new Vector2();
    }

    static Vector2 one() {
        return *new Vector2(1, 1);
    }

    static int Dot(Vector2 a, Vector2 b) {
        int product = 0;
        for (int i = 0; i < 2; i++) product = product + a[i] * b[i];
        return product;
    }

    float operator [] (int i) {
        if (i == 0) return this->x;
        if (i == 1) return this->y;
        throw "Trying to access invalid member of Vector2";
    }

    Vector2 operator + (Vector2 const& obj) {
        Vector2 res;
        res.x = this->x + obj.x;
        res.y = this->y + obj.y;
        return res;
    }

    Vector2 operator * (float obj) {
        Vector2 res;
        res.x = this->x * obj;
        res.y = this->y * obj;
        return res;
    }

    Vector2 operator / (float obj) {
        Vector2 res;
        res.x = this->x / obj;
        res.y = this->y / obj;
        return res;
    }
};

