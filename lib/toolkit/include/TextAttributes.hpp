#ifndef VERTEX_TEXT_ATTRIBUTES_HPP
#define VERTEX_TEXT_ATTRIBUTES_HPP

#include "raylib.h"

namespace vertex {
	struct TextAttributes {
		Font TextFont = GetFontDefault();
		Color TextColor = BLACK;
		float TextSize = 20.0f;
	};
}

#endif
