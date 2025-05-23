#pragma once
#include <string>
#include "Vector2.h"

constexpr int ScreenWidth = 75;
constexpr int ScreenHeight = 40;

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
    ~GraphicsManager();

    static GraphicsManager& instance()
    {
        if (!m_instance)
        {
            m_instance = new GraphicsManager;
        }
        return *m_instance;
    }

    // 指定した文字描画
    void Printf(Vector2 pos, std::string  dispChar,
        DrawColor textColor, TextPivot pivot = TextPivot::Left,
        DrawColor backColor = DrawColor(0, 0, 0));
    void Printf(Vector2 pos, std::string  dispChar, TextPivot pivot = TextPivot::Left);
    void Printf(Vector2 pos, std::string  dispChar,
        DrawColor textColor = DrawColor(1, 1, 1),
        DrawColor backColor = DrawColor(0, 0, 0));

    // 円の描画
    void DrawCircle(Vector2 pos, float radius,
        DrawColor textColor = DrawColor(1, 1, 1),
        DrawColor backColor = DrawColor(0, 0, 0),
        std::string  dispChar = "■");

    // 四角形の描画
    void DrawRect(Vector2 pos, Vector2 size,
        DrawColor textColor = DrawColor(1, 1, 1),
        DrawColor backColor = DrawColor(0, 0, 0),
        std::string  dispChar = "■");

    // 線の描画
    void DrawLine(Vector2 start, Vector2 end,
        DrawColor textColor = DrawColor(1, 1, 1),
        DrawColor backColor = DrawColor(0, 0, 0) ,
        std::string  dispChar = "■");

    // 描画前準備
    void RenderPrepar();

    // 画面描画※フレームワークで1回のみ呼ぶ用
    void Render();

public:
    DisplayDot display[ScreenWidth][ScreenHeight] = {};

private:
    static GraphicsManager* m_instance;
};