#pragma once
#include "Scene.h"
#include <memory>
#include <vector>
#include "Ray.h"

class Player {
public:
    Player() :pos(0, 0), angle(0) {}
public:
    Vector2 pos;
    float angle;
};

class SceneTest :public Scene
{
public:
    SceneTest() ;
    ~SceneTest() {};

    void Update()override;

private:
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Ray>> walls;
    std::vector<std::unique_ptr<Ray>> glids;
};