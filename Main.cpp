#include <time.h>
#include "GraphicsManager.h"
#include "SceneManager.h"
#include "SceneTest.h"
#include "SceneTest2.h"

constexpr int updateFps = 60;
constexpr int updateInterval = 1000 / updateFps;
constexpr int drawFps = 30;
constexpr int drawInterval = 1000 / drawFps;

int main()
{
    std::unique_ptr<SceneManager> sceneManager = std::make_unique<SceneManager>();
    sceneManager->ChengeScene(std::make_unique<SceneTest>());

    clock_t lastUpdateClock = clock();
    clock_t lastDrawClock = clock();
    while (true)
    {
        clock_t nowClock = clock();

        if (nowClock >= lastUpdateClock + updateInterval)
        {
            lastUpdateClock = nowClock;

            // 描画前準備
            GraphicsManager::instance().RenderPrepar();

            sceneManager->Update();
        }

        if (nowClock >= lastDrawClock + drawInterval)
        {
            lastDrawClock = nowClock;
            GraphicsManager::instance().Render();
        }
    }
    return 1;
}