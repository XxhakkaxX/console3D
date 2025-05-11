#include "GraphicsManager.h"
#include <algorithm>

GraphicsManager::GraphicsManager() :display() 
{
}

void GraphicsManager::Printf(Vector2 pos, const char* dispChar, DrawColor textColor, TextPivot pivot, DrawColor backColor)
{
    display[static_cast<int>(pos.x)][static_cast<int>(pos.y)].textColor = textColor;
    display[static_cast<int>(pos.x)][static_cast<int>(pos.y)].backColor = backColor;
    Printf(pos, dispChar, pivot);
}

void GraphicsManager::Printf(Vector2 pos, const char* dispChar, TextPivot pivot)
{
    std::string str = dispChar;
    for (int i = 0; i < str.length(); ++i)
    {
        int setPosX = static_cast<int>(pos.x) + i;
        if (pivot == TextPivot::Center)
        {
            setPosX -= static_cast<int>(str.length() * 0.5f);
        }
        if (pivot == TextPivot::Right)
        {
            setPosX -= static_cast<int>(str.length());
        }
        if (setPosX < 0 || setPosX > ScreenWidth - 1) continue;
        if (pos.y < 0 || pos.y > ScreenHeight - 1) continue;
        display[setPosX][static_cast<int>(pos.y)].text = str[i];
    }
}

void GraphicsManager::DrawLine(Vector2 start, Vector2 end,
    DrawColor textColor,
    DrawColor backColor, const char* dispChar)
{
    int i = 0;
    // 軽量化余地あり
    while (true)
    {
        auto vec = end - start;
        auto dispPos = start + vec.normalize() * i;

        // 描画範囲内かチェック
        auto displayCheck = [&]()
            {
                return (abs(dispPos.lengthSq(end)) < 0.25f || abs(dispPos.lengthSq(end)) > abs(start.lengthSq(end)));
            };

        if (dispPos.x < 0 || dispPos.y < 0 || dispPos.x >= ScreenWidth || dispPos.y >= ScreenHeight)
        {
            ++i;
            if (displayCheck()){ break;}
            continue;
        }
        
        display[static_cast<int>(dispPos.x)][static_cast<int>(dispPos.y)].textColor = textColor;
        display[static_cast<int>(dispPos.x)][static_cast<int>(dispPos.y)].backColor = backColor;
        display[static_cast<int>(dispPos.x)][static_cast<int>(dispPos.y)].text = dispChar;
        ++i;
        if (displayCheck()){ break;}
    }
}

void GraphicsManager::RenderPrepar()
{
    for (int y = 0; y < ScreenHeight; ++y)
    {
        for (int x = 0; x < ScreenWidth; ++x)
        {
            display[x][y].backColor = { 0,0,0 };
            display[x][y].textColor = { 1,1,1 };
            display[x][y].text = "　";
        }
    }
}

void GraphicsManager::Render()
{
    std::system("cls");
    for (int y = 0; y < ScreenHeight; ++y)
    {
        for (int x = 0; x < ScreenWidth; ++x)
        {
            std::string disp =
                "\x1b[48;2;" +
                std::to_string(static_cast<int>(256 * std::clamp(display[x][y].backColor.r, 0.0f, 1.0f))) + ";" +
                std::to_string(static_cast<int>(256 * std::clamp(display[x][y].backColor.g, 0.0f, 1.0f))) + ";" +
                std::to_string(static_cast<int>(256 * std::clamp(display[x][y].backColor.b, 0.0f, 1.0f))) + "m" +
                "\x1b[38;2;" +
                std::to_string(static_cast<int>(256 * std::clamp(display[x][y].textColor.r, 0.0f, 1.0f))) + ";" +
                std::to_string(static_cast<int>(256 * std::clamp(display[x][y].textColor.g, 0.0f, 1.0f))) + ";" +
                std::to_string(static_cast<int>(256 * std::clamp(display[x][y].textColor.b, 0.0f, 1.0f))) + "m" +
                display[x][y].text;

            printf(disp.c_str());
        }
        printf("\n");
    }
}
