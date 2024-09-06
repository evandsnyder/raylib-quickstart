#ifndef VERTEX_MENU_HPP
#define VERTEX_MENU_HPP

#include "raylib.h"
#include "TextAttributes.hpp"
#include "MenuOption.hpp"
#include "BoxAttributes.hpp"

#include <vector>

namespace vertex {
	class Menu {
	public:
		Menu(float PositionX, float PositionY, float Width, float Height);

		void SetPosition(float NewPositionX, float NewPositionY);
		void SetHeight(float NewHeight);
		void SetWidth(float NewWidth);
		void SetBackgroundColor(Color NewColor);

		void AddMenuOption(const MenuOption& NewOption);

		void Draw() const;
	private:
		std::vector<MenuOption> MenuOptions;

		TextAttributes MenuTextAttributes;
		BoxAttributes MenuBoxAttributes;

		int HighlightedIndex = 0;

	};
}

#endif
