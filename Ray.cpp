#include "Ray.h"
#include <math.h>
#include <iostream>

Ray::Ray(Vector2 pos, Vector2 way) :pos(pos), vec(way - pos)
{}

bool Ray::intersection(const Ray* input, Vector2& ret)
{
    auto r2 = *input;

    // Y�����s�̐����͂��̃R�[�h�ł͈����Ȃ��̂ŁA���s�̏ꍇ�͔����ɂ��炷
    if (abs(vec.x) < 0.01)  vec.x = 0.01;
    if (abs(r2.vec.x) < 0.01) r2.vec.x = 0.01;

    // r1,r2�𒼐��Ƃ��Č��āA���̌�_�����߂�
    auto t1 = vec.y / vec.x;
    auto t2 = r2.vec.y / r2.vec.x;
    auto x1 = pos.x;
    auto x2 = r2.pos.x;
    auto y1 = pos.y;
    auto y2 = r2.pos.y;
    auto sx = (t1 * x1 - t2 * x2 - y1 + y2) / (t1 - t2);
    auto sy = t1 * (sx - x1) + y1;

    // ��_��������ɂȂ��Ƃ���null��Ԃ�
    if (
        sx > std::min(begin().x, end().x)
        && sx < std::max(begin().x, end().x)
        && sx > std::min(r2.begin().x, r2.end().x)
        && sx < std::max(r2.begin().x, r2.end().x)
        ) {
        ret = Vector2(sx, sy);
        return true;
    }
    return false;
}
