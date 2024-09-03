#ifndef VERTEX_DIALOGBOX_HPP
#define VERTEX_DIALOGBOX_HPP

#include <string>
#include <raylib.h>

namespace vertex {
	class DialogBox {
	public:
		DialogBox(float ScreenPositionX, float ScreenPositionY, float Width, float Height);

		void SetPosition(float NewPositionX, float NewPositionY);
		void SetBounds(float Width, float Height);
		void SetFont(Font NewFont);

		void SetText(const std::string& text);
		void SetTextColor();
		void Draw();

	private:
		Color TextColor = BLACK;
		Color BorderColor = BLACK;

		Rectangle BorderRectangle;
		Font TextFont;

		std::string TargetText;
	};
}

#endif
