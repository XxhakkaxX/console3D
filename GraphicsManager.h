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

    // éwíËÇµÇΩï∂éöï`âÊ
    void Printf(Vector2 pos, std::string  dispChar,
        DrawColor textColor, TextPivot pivot = TextPivot::Left,
        DrawColor backColor = DrawColor(0, 0, 0));
    void Printf(Vector2 pos, std::string  dispChar, TextPivot pivot = TextPivot::Left);
    void Printf(Vector2 pos, std::string  dispChar,
        DrawColor textColor = DrawColor(1, 1, 1),
        DrawColor backColor = DrawColor(0, 0, 0));

    // â~ÇÃï`âÊ
    void DrawCircle(Vector2 pos, float radius,
        DrawColor textColor = DrawColor(1, 1, 1),
        DrawColor backColor = DrawColor(0, 0, 0),
        std::string  dispChar = "Å°");

    // éläpå`ÇÃï`âÊ
    void DrawRect(Vector2 pos, Vector2 size,
        DrawColor textColor = DrawColor(1, 1, 1),
        DrawColor backColor = DrawColor(0, 0, 0),
        std::string  dispChar = "Å°");

    // ê¸ÇÃï`âÊ
    void DrawLine(Vector2 start, Vector2 end,
        DrawColor textColor = DrawColor(1, 1, 1),
        DrawColor backColor = DrawColor(0, 0, 0) ,
        std::string  dispChar = "Å°");

    // ï`âÊëOèÄîı
    void RenderPrepar();

    // âÊñ ï`âÊÅ¶ÉtÉåÅ[ÉÄÉèÅ[ÉNÇ≈1âÒÇÃÇ›åƒÇ‘óp
    void Render();

public:
    DisplayDot display[ScreenWidth][ScreenHeight] = {};

private:
    static GraphicsManager* m_instance;
};