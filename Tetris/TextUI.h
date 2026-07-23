#pragma once

#include <raylib.h>
#include <string>

class TextUI {

public:
    enum class HorizontalAlignment {
        Left,
        Center,
        Right
    };
    enum class VerticalAlignment {
        Top,
        Middle,
        Bottom
    };

    TextUI();
	TextUI(Font _font, std::string _text, Vector2 _anchorPos, int _fontSize, int _spacing, Color _color, HorizontalAlignment hAnchorAlign, VerticalAlignment vAnchorAlign);
    void SetText(std::string _text);
    void Draw();
    Vector2 GetTextAnchorPos();
    Vector2 textSize;

private:
    void UpdateDrawPos();
	Font font;
    std::string text;
	Vector2 anchorPos;
    int fontSize;
    int spacing;
    Color color;
    HorizontalAlignment hAnchorAlignment;
    VerticalAlignment vAnchorAlignment;
    Vector2 drawPos;
};