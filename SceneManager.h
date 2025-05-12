#pragma once
#include <memory>
#include "Scene.h"
#include <iostream>
#include <utility>

class SceneManager
{
public:
    SceneManager();

    //template<class T>
    void ChengeScene(std::unique_ptr<Scene> newScene)
    {
        currentScene.reset();
        currentScene = nullptr;
        currentScene = std::move(newScene);
        //std::unique_ptr<Scene>(static_cast<Scene*>(newScene.release()));
    };

    void Update();
public:
    std::unique_ptr<Scene> currentScene;
};


