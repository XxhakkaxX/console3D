#include "SceneTest.h"

#include <algorithm>
#include <conio.h>
#include <iostream>
#include <Windows.h>

#include "Util.h"
#include "GraphicsManager.h"

SceneTest::SceneTest()
{
    player = std::make_unique<Player>();
    player->pos = { 110,200 };
    player->angle = -PI / 2;

    walls.emplace_back(std::make_unique<Ray>(Vector2(50, 50), Vector2(100, 300)));
    walls.emplace_back(std::make_unique<Ray>(Vector2(100, 300), Vector2(250, 200)));
    walls.emplace_back(std::make_unique<Ray>(Vector2(250, 200), Vector2(50, 50)));

    for (int i = 0; i < 600; i += 50)
    {
        glids.emplace_back(std::make_unique<Ray>(Vector2(0, i), Vector2(500, i)));
        glids.emplace_back(std::make_unique<Ray>(Vector2(i, 0), Vector2(i, 500)));
    }
}

void SceneTest::Update()
{
    GraphicsManager& graphics = GraphicsManager::instance();
    const float moveSpeed = 5.0f;

    if (GetKeyState('W') < 0)
    {
        player->pos.x += moveSpeed * cos(player->angle);
        player->pos.y += moveSpeed * sin(player->angle);
    }
    if (GetKeyState('S') < 0)
    {
        player->pos.x -= moveSpeed * cos(player->angle);
        player->pos.y -= moveSpeed * sin(player->angle);
    }
    if (GetKeyState('D') < 0)
    {
        player->pos.x += moveSpeed * cos(player->angle + PI * 0.5f);
        player->pos.y += moveSpeed * sin(player->angle + PI * 0.5f);
    }
    if (GetKeyState('A') < 0)
    {
        player->pos.x += moveSpeed * cos(player->angle - PI * 0.5f);
        player->pos.y += moveSpeed * sin(player->angle - PI * 0.5f);
    }
    if (GetKeyState('J') < 0)
    {
        player->angle -= PI / 15;
    }
    if (GetKeyState('L') < 0)
    {
        player->angle += PI / 15;
    }

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

        for (auto& glid : glids)
        {
            Vector2 hitPos(0, 0);
            auto hit = beam.intersection(glid.get(), hitPos);
            if (!hit) continue;
            // 3Dビューに描画
            auto viewRoot = Vector2(0, ScreenHeight * 0.5f);
            auto wallDist = (hitPos - beam.begin()).len();
            auto wallPerpDist = wallDist * cos(angle - centerAngle);
            auto lineHeight = std::clamp(1400 / wallPerpDist, 0.0f, (float)ScreenHeight);
            auto lineBegin = viewRoot + Vector2(beamIndex, -lineHeight / 2);
            auto lineEnd = lineBegin + Vector2(0, lineHeight);
            float fogColor = 1 - (wallDist / 150);

            graphics.Printf(lineEnd, "■", DrawColor(fogColor, fogColor, fogColor), DrawColor(0, 0, 0));
        }

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

            graphics.DrawLine(lineBegin, lineEnd, DrawColor(fogColor, fogColor, fogColor));
        }
    }

    graphics.Printf(Vector2(1, ScreenHeight * 0.5f + 3), "デバッグが", DrawColor(1, 1, 1), TextPivot::Left);
    graphics.Printf(Vector2(0, ScreenHeight * 0.5f + 2), "[、ツール] -> [オプション] -> [デバッグ] -> [デバッグの停止時に自動的にコンソールを閉じる] を有効にします", DrawColor(1, 1, 1), TextPivot::Left);
    graphics.Printf(Vector2(0, ScreenHeight * 0.5f + 1), "このウィンドウを閉じるには、任意のキーを押してください..", DrawColor(1, 1, 1), TextPivot::Left);
    graphics.Printf(Vector2(0, ScreenHeight * 0.5f ), "３Dtest.exe (プロセス 14832) は、コード -1 で終了しました。", DrawColor(1, 1, 1), TextPivot::Left);
    //std::printf("💣");
    //std::printf("あ");
}
