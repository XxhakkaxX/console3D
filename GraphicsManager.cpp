#include "GraphicsManager.h"
#include <algorithm>
#include <windows.h>

GraphicsManager::GraphicsManager() :display() 
{
}

void GraphicsManager::Printf(Vector2 pos, std::string  dispChar, DrawColor textColor, TextPivot pivot, DrawColor backColor)
{
    if (pos.x < 0 || pos.x > ScreenWidth - 1) return;
    if (pos.y < 0 || pos.y > ScreenHeight - 1) return;
    display[static_cast<int>(pos.x)][static_cast<int>(pos.y)].textColor = textColor;
    display[static_cast<int>(pos.x)][static_cast<int>(pos.y)].backColor = backColor;
    Printf(pos, dispChar, pivot);
}

void GraphicsManager::Printf(Vector2 pos, std::string  dispChar, TextPivot pivot)
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

void GraphicsManager::Printf(Vector2 pos, std::string dispChar,
    DrawColor textColor ,
    DrawColor backColor )
{
    if (pos.x < 0 || pos.x > ScreenWidth - 1) return;
    if (pos.y < 0 || pos.y > ScreenHeight - 1) return;
    display[static_cast<int>(pos.x)][static_cast<int>(pos.y)].textColor = textColor;
    display[static_cast<int>(pos.x)][static_cast<int>(pos.y)].backColor = backColor;
    display[static_cast<int>(pos.x)][static_cast<int>(pos.y)].text = dispChar;
}

void GraphicsManager::DrawCircle(Vector2 pos, float radius, DrawColor textColor, DrawColor backColor, std::string  dispChar)
{
    for (int y = 0; y < static_cast<int>(radius * 2); ++y)
    {
        for (int x = 0; x < static_cast<int>(radius * 2); ++x)
        {
            int setPosX = static_cast<int>(pos.x) + x - static_cast<int>(radius);
            int setPosY = static_cast<int>(pos.y) + y - static_cast<int>(radius);
            if (pos.lengthSq(Vector2(setPosX, setPosY)) > static_cast<int>(radius * radius)) continue;
            if (setPosX < 0 || setPosX > ScreenWidth - 1) continue;
            if (setPosY < 0 || setPosY > ScreenHeight - 1) continue;
            display[setPosX][setPosY].textColor = textColor;
            display[setPosX][setPosY].backColor = backColor;
            display[setPosX][setPosY].text = dispChar;
        }
    }
}

void GraphicsManager::DrawRect(Vector2 pos, Vector2 size, DrawColor textColor, DrawColor backColor, std::string  dispChar)
{
    for (int y = 0; y < size.y; ++y)
    {
        for (int x = 0; x < size.x; ++x)
        {
            int setPosX = static_cast<int>(pos.x) + x - static_cast<int>(size.x * 0.5f);
            int setPosY = static_cast<int>(pos.y) + y - static_cast<int>(size.y * 0.5f);
            if (setPosX < 0 || setPosX > ScreenWidth - 1) continue;
            if (setPosY < 0 || setPosY > ScreenHeight - 1) continue;
            display[setPosX][setPosY].textColor = textColor;
            display[setPosX][setPosY].backColor = backColor;
            display[setPosX][setPosY].text = dispChar;
        }
    }
}

void GraphicsManager::DrawLine(Vector2 start, Vector2 end,
    DrawColor textColor,
    DrawColor backColor, std::string  dispChar)
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
    //std::system("cls");
    HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = 0;
    pos.Y = 0;
    SetConsoleCursorPosition(hCons, pos);

    CONSOLE_CURSOR_INFO cci;

    // CONSOLE_CURSOR_INFO構造体の現在の状態を取得する
    GetConsoleCursorInfo(hCons, &cci);

    // メンバ変数であるbVisibleがカーソルの表示・非表示を制御する変数なので、これをFALSEにする事でカーソルを非表示にできる
    cci.bVisible = FALSE;

    // 変更した構造体情報をコンソールWindowにセットする
    SetConsoleCursorInfo(hCons, &cci);
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
