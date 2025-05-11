#include <iostream>
#include <algorithm>
#include <conio.h>
#include <vector>
#include <time.h>
#include "Vector2.h"
#include "Ray.h"
#include "GraphicsManager.h"

class Player {
public:
    Player() :pos(0, 0), angle(0) {}
public:
    Vector2 pos;
    float angle;
};

int main()
{
    std::unique_ptr<GraphicsManager> graphics = std::make_unique<GraphicsManager>();
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Ray>> walls;
    constexpr float PI = 3.141592654f;

    const int updateFps = 60;
    const int updateInterval = 1000 / updateFps;

    const int drawFps = 10;
    const int drawInterval = 1000 / drawFps;

    clock_t lastUpdateClock = clock();
    clock_t lastDrawClock = clock();

    player = std::make_unique<Player>();
    player->pos = { 110,200 };
    player->angle = -PI / 2;
    const float moveSpeed = 5.0f;

    walls.emplace_back(std::make_unique<Ray>(Vector2(50, 50), Vector2(100, 300)));
    walls.emplace_back(std::make_unique<Ray>(Vector2(100, 300), Vector2(250, 200)));
    walls.emplace_back(std::make_unique<Ray>(Vector2(250, 200), Vector2(50, 50)));

    while (true)
    {
        clock_t nowClock = clock();

        if (nowClock >= lastUpdateClock + updateInterval)
        {
            lastUpdateClock = nowClock;


            if (_kbhit())
            {
                switch (_getch())
                {
                case 'w':
                    player->pos.x += moveSpeed * cos(player->angle);
                    player->pos.y += moveSpeed * sin(player->angle);
                    break;
                case 's':
                    player->pos.x -= moveSpeed * cos(player->angle);
                    player->pos.y -= moveSpeed * sin(player->angle);
                    break;
                case 'd':
                    player->pos.x += moveSpeed * cos(player->angle + PI * 0.5f);
                    player->pos.y += moveSpeed * sin(player->angle + PI * 0.5f);
                    break;
                case 'a':
                    player->pos.x += moveSpeed * cos(player->angle - PI * 0.5f);
                    player->pos.y += moveSpeed * sin(player->angle - PI * 0.5f);
                    break;
                case 'j':
                    player->angle -= PI / 30;
                    break;
                case 'l':
                    player->angle += PI / 30;
                    break;
                }
            }

            // 描画前準備
            graphics->RenderPrepar();


            // プレイヤーの視界を表現
            auto fov = PI / 2;
            auto centerAngle = player->angle;
            auto leftAngle = centerAngle - fov / 2;
            auto rightAngle = centerAngle + fov / 2;
            auto beamIndex = -1;
            for (auto angle = leftAngle; angle < rightAngle + 0.01; angle += fov / ScreenWidth) {
                beamIndex++;
                float playerEyeLen = 1000;
                auto beam = Ray(player->pos, Vector2(cos(angle) * playerEyeLen, sin(angle) * playerEyeLen));
                float neerLen = FLT_MAX;
                for (auto& wall : walls) {
                    Vector2 hitPos(0, 0);
                    auto hit = beam.intersection(wall.get(), hitPos);
                    if (!hit) continue;
                    // 3Dビューに描画
                    auto viewRoot = Vector2(0, ScreenHeight * 0.5f);
                    auto wallDist = (hitPos - beam.begin()).len();
                    auto wallPerpDist = wallDist * cos(angle - centerAngle);
                    auto lineHeight = std::clamp(1400 / wallPerpDist, 0.0f, (float)ScreenHeight);
                    auto lineBegin = viewRoot + Vector2(beamIndex, -lineHeight / 2);
                    auto lineEnd = lineBegin + Vector2(0, lineHeight);

                    if (lineBegin.len() > ScreenWidth * ScreenHeight)continue;
                    if (lineEnd.len() > ScreenWidth * ScreenHeight)continue;
                    // 重なった場合は近い壁のみ描画
                    if (neerLen < wallDist)continue;
                    neerLen = wallDist;
                    float fogColor = 1 - (wallDist / 150);
                
                    graphics->DrawLine(lineBegin, lineEnd, DrawColor(fogColor, fogColor, fogColor));
                }
            }
            
            graphics->Printf(Vector2(3, 3), "TEST");
        }

        if (nowClock >= lastDrawClock + drawInterval)
        {
            lastDrawClock = nowClock;
            graphics->Render();
        }
    }
    return 1;
}