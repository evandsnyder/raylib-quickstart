#include "dialogbox.hpp"


namespace vertex {
	DialogBox::DialogBox(float ScreenPositionX, float ScreenPositionY, float Width, float Height)
		: BorderRectangle(Rectangle{ ScreenPositionX, ScreenPositionY, Width, Height }) {
	}

	void DialogBox::SetPosition(float NewPositionX, float NewPositionY) {
		BorderRectangle.x = NewPositionX;
		BorderRectangle.y = NewPositionY;
	}

	void DialogBox::SetBounds(float Width, float Height) {
		BorderRectangle.height = Height;
		BorderRectangle.width = Width;
	}

	void DialogBox::SetFont(Font NewFont) {
		TextFont = NewFont;
	}

	void DialogBox::SetText(const std::string& text)
	{
		TargetText = text;
	}

	void DialogBox::Draw()
	{
		DrawRectangleLinesEx(BorderRectangle, 3, BorderColor);

		Rectangle TextBox = { BorderRectangle.x - 4, BorderRectangle.y - 4, BorderRectangle.width - 4, BorderRectangle.height - 4 };
		float FontSize;
		Color Tint;
		int SelectStart;
		int SelectLength;
		Color SelectTint;
		Color SelectBlackTint;

		float TextOffsetY = 0.0f;
		float TextOffsetX = 0.0f;
		float ScaleFactor = FontSize / static_cast<float>(TextFont.baseSize);
	}
}
