#include "SceneManager.h"


SceneManager::SceneManager() :currentScene(nullptr)
{
}

void SceneManager::ChengeScene(std::unique_ptr<Scene> newScene)
{
    currentScene.reset();
    currentScene = nullptr;
    currentScene = std::move(newScene);
};

void SceneManager::Update()
{
    if (currentScene)
    {
        currentScene->Update();
    }
}
