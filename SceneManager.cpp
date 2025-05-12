#include "SceneManager.h"


SceneManager::SceneManager() :currentScene(nullptr)
{
}

void SceneManager::Update()
{
    if (currentScene)
    {
        currentScene->Update();
    }
}
