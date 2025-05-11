#include "Vector2.h"
#include <math.h>

Vector2::Vector2(float x, float y) : x(x), y(y) 
{
}

float Vector2::len()
{
    return sqrtf(powf(x, 2) + powf(y, 2));
}

float Vector2::lengthSq(const Vector2& input)
{
    return powf(x - input.x, 2) + powf(y - input.y, 2);
}

float Vector2::length(const Vector2& input)
{
    return sqrtf(lengthSq(input));
}

Vector2 Vector2::normalize()
{
    float rate = len();
    if (rate == 0)return Vector2(x / 0.001f, y / 0.001f);
    return Vector2(x / rate, y / rate);
}

float Vector2::dot(const Vector2& input)
{
    return (x * input.x) + (y * input.y);
}

