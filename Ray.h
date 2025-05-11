#pragma once
#include "Vector2.h"

class Ray {
public:
    Ray(Vector2 pos, Vector2 way);

    Vector2 begin() { return pos; }
    Vector2 end() { return pos + vec; }

    // ���̃��C�ƁAinput�̌�_�����߂�B
    bool intersection(const Ray* input, Vector2& ret);
public:
    Vector2  pos;
    Vector2  vec;
};