#pragma once
class Vector2 {
public:
    Vector2(float x, float y);

    Vector2 operator+(const Vector2& input)
    {
        return Vector2(input.x + x, input.y + y);
    }
    Vector2 operator+=(const Vector2& input)
    {
        return Vector2(input.x + x, input.y + y);
    }
    Vector2 operator-(const Vector2& input)
    {
        return Vector2(x - input.x, y - input.y);
    }
    Vector2 operator-=(const Vector2& input)
    {
        return Vector2(x - input.x, y - input.y);
    }
    Vector2 operator*(const float& input)
    {
        return Vector2(x * input, y * input);
    }
    Vector2 operator*=(const float& input)
    {
        return Vector2(x * input, y * input);
    }

    float len();
    float lengthSq(const Vector2& input);
    float length(const Vector2& input);
    Vector2 normalize();
    float dot(const Vector2& input);

public:
    float x;
    float y;
};
