#include "TextUI.h"

// Default constructor
TextUI::TextUI()
{
	anchorPos = { 0, 0 };
	fontSize = 38;
	spacing = 2;
	color = WHITE;
	hAnchorAlignment = HorizontalAlignment::Left;
	vAnchorAlignment = VerticalAlignment::Top;
}

// Overload constructor
TextUI::TextUI(Font _font, std::string _text, Vector2 _anchorPos, int _fontSize, int _spacing, Color _color, HorizontalAlignment hAnchorAlign, VerticalAlignment vAnchorAlign)
{
	font = _font;
	anchorPos = _anchorPos;
	fontSize = _fontSize;
	spacing = _spacing;
	color = _color;
	hAnchorAlignment = hAnchorAlign;
	vAnchorAlignment = vAnchorAlign;

	SetText(_text); // Set text and update text size and draw position
}


// Setter method for text content and updates the text size and draw position
void TextUI::SetText(std::string _text)
{
	text = _text;
	textSize = MeasureTextEx(font, text.c_str(), fontSize, spacing);
	UpdateDrawPos(); // Update draw position since text size is used in the calculation
}


// Draws text at draw position
void TextUI::Draw()
{
	DrawTextEx(font, text.c_str(), drawPos, fontSize, spacing, color);
}


// Returns the anchor position of the text
Vector2 TextUI::GetTextAnchorPos()
{
	return anchorPos;
}


// Updates the draw position of the text based on the anchor position and alignment settings
void TextUI::UpdateDrawPos()
{
	switch (hAnchorAlignment)
	{
		case HorizontalAlignment::Left:
			drawPos.x = anchorPos.x;
			break;
		case HorizontalAlignment::Center:
			drawPos.x = anchorPos.x - textSize.x / 2;
			break;
		case HorizontalAlignment::Right:
			drawPos.x = anchorPos.x - textSize.x;
			break;
	}

	switch (vAnchorAlignment)
	{
	case VerticalAlignment::Top:
		drawPos.y = anchorPos.y;
		break;
	case VerticalAlignment::Middle:
		drawPos.y = anchorPos.y - textSize.y / 2;
		break;
	case VerticalAlignment::Bottom:
		drawPos.y = anchorPos.y - textSize.y;
		break;
	}
}
