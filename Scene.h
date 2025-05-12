#pragma once
class Scene
{
public:
    virtual ~Scene() = default;
    virtual void Update() = 0;
};