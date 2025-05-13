#pragma once
#include <memory>
#include "Scene.h"
#include <iostream>
#include <utility>

class SceneManager
{
public:
    SceneManager();

    void ChengeScene(std::unique_ptr<Scene> newScene);

    void Update();
public:
    std::unique_ptr<Scene> currentScene;
};


