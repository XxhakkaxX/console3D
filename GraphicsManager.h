#pragma once
#include <string>
#include "Vector2.h"

constexpr int ScreenWidth = 80;
constexpr int ScreenHeight = 50;

struct DrawColor
{
    float r;
    float g;
    float b;
};

struct DisplayDot
{
    DrawColor textColor{0,0,0};
    DrawColor backColor{0,0,0};
    std::string text{};
};

enum class TextPivot
{
    Left,
    Center,
    Right,
    TARM
};

class GraphicsManager
{
public:
    GraphicsManager();

    // 指定した文字描画
    void Printf(Vector2 pos, const char* dispChar,
        DrawColor textColor, TextPivot pivot = TextPivot::Left,
        DrawColor backColor = DrawColor(0, 0, 0));
    void Printf(Vector2 pos, const char* dispChar, TextPivot pivot = TextPivot::Left);

    // 線の描画
    void DrawLine(Vector2 start, Vector2 end,
        DrawColor textColor = DrawColor(1, 1, 1),
        DrawColor backColor = DrawColor(0, 0, 0) ,
        const char* dispChar = "■");

    // 描画前準備
    void RenderPrepar();

    // 画面描画※フレームワークで1回のみ呼ぶ用
    void Render();

public:
    DisplayDot display[ScreenWidth][ScreenHeight] = {};
};