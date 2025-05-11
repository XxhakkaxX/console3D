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

    // �w�肵�������`��
    void Printf(Vector2 pos, const char* dispChar,
        DrawColor textColor, TextPivot pivot = TextPivot::Left,
        DrawColor backColor = DrawColor(0, 0, 0));
    void Printf(Vector2 pos, const char* dispChar, TextPivot pivot = TextPivot::Left);

    // ���̕`��
    void DrawLine(Vector2 start, Vector2 end,
        DrawColor textColor = DrawColor(1, 1, 1),
        DrawColor backColor = DrawColor(0, 0, 0) ,
        const char* dispChar = "��");

    // �`��O����
    void RenderPrepar();

    // ��ʕ`�恦�t���[�����[�N��1��̂݌Ăԗp
    void Render();

public:
    DisplayDot display[ScreenWidth][ScreenHeight] = {};
};