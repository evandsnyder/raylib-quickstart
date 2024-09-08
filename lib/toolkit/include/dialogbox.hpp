#ifndef VERTEX_DIALOGBOX_HPP
#define VERTEX_DIALOGBOX_HPP

#include <string>
#include <raylib.h>

namespace vertex {
	class DialogBox {
	public:
		DialogBox(float ScreenPositionX, float ScreenPositionY, int Width, int Height);
		DialogBox(float ScreenPositionX, float ScreenPositionY, float Width, float Height);


		void SetPosition(float NewPositionX, float NewPositionY);
		void SetBounds(float Width, float Height);
		void SetFont(const Font& NewFont);
		void SetFontSize(float NewFontSize);

		void SetMinimumWidth(float NewMinimumWidth);
		void SetMaximumWidth(float NewMaximumWidth);
		void SetMinimumHeight(float NewMinimumHeight);
		void SetMaximumHeight(float NewMaximumHeight);

		void SetText(const std::string& NewText);
		void SetTextColor(const Color& NewColor);

		void SetBorderColor(const Color& NewColor);
		void SetBackgroundColor(const Color& NewColor);

		void SetShouldAnimateText(bool NewAnimate);

		void Draw();

	private:
		float MinimumWidth;
		float MaximumWidth;
		float MinimumHeight;
		float MaximumHeight;

		Color TextColor;
		Color BorderColor;
		Color BackgroundColor;

		Rectangle BorderRectangle;
		Font TextFont;
		float FontSize;

		std::string TargetText;

		float GlyphSpacing = 2.0f;
		int FrameCounter = 0;
		int DrawSpeed = 8;

		bool ShouldAnimateText = true;
	};
}

#endif
