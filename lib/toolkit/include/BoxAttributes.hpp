#ifndef VERTEX_BOX_ATTRIBUTES_HPP
#define VERTEX_BOX_ATTRIBUTES_HPP

#include "raylib.h"

namespace vertex {
	constexpr float BORDER_NONE = 0.0f;
	constexpr float BORDER_DEFAULT = 3.0f;

	struct BoxAttributes{
		Rectangle Rect;
		Color BackgroundColor = WHITE;
		Color BorderColor = BLACK;

		float BorderThickness = BORDER_DEFAULT;

		BoxAttributes(float PositionX, float PositionY, float Width, float Height);
	};

	void DrawBox(const BoxAttributes& Attributes);
}

#endif
