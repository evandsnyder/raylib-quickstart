#include "Menu.hpp"

namespace vertex
{
	Menu::Menu(float PositionX, float PositionY, float Width, float Height)
		:
		MenuOptions(),
		MenuTextAttributes(),
		MenuBoxAttributes(PositionX, PositionY, Width, Height)
	{
	}

	void Menu::SetPosition(float NewPositionX, float NewPositionY)
	{
		MenuBoxAttributes.Rect.x = NewPositionX;
		MenuBoxAttributes.Rect.y = NewPositionY;
	}

	void Menu::SetHeight(float NewHeight)
	{
		MenuBoxAttributes.Rect.height = NewHeight;
	}

	void Menu::SetWidth(float NewWidth)
	{
		MenuBoxAttributes.Rect.width = NewWidth;
	}

	void Menu::SetBackgroundColor(Color NewColor)
	{
		MenuBoxAttributes.BackgroundColor = NewColor;
	}

	void Menu::AddMenuOption(const MenuOption& NewOption)
	{

		MenuOptions.push_back(NewOption);
		// TODO: Add some kind of subscription to track when label gets changed
	}

	void Menu::Draw() const
	{
		// TODO: Can we calculate width of the box based on the largest word...

		// Find largest word and make box large enough for it...
		size_t LargestWord = 0;
		for (auto const& Option : MenuOptions)
		{
			LargestWord = std::max(LargestWord, Option.GetLabel().size());
		}

		// Set the width to the largest word...
		

		DrawBox(MenuBoxAttributes);
		const int FontBaseSize = MenuTextAttributes.TextFont.baseSize;
		const float ScaleFactor = MenuTextAttributes.TextSize / static_cast<float>(FontBaseSize);
		const int VerticalOffsetIncrement = (FontBaseSize + FontBaseSize / 2) * ScaleFactor;


		const int OffsetX = static_cast<int>(MenuBoxAttributes.Rect.x) + 24;
		int OffsetY = static_cast<int>(MenuBoxAttributes.Rect.y) + 8;

		for (int i = 0; i < MenuOptions.size(); i++)
		{
			const MenuOption& Option = MenuOptions[i];

			if (HighlightedIndex == i)
			{
				const Vector2 TrianglePosition = { static_cast<float>(OffsetX - 16), static_cast<float>(OffsetY + 4 + (FontBaseSize / 2)) };
				// I kind of brute-forced the midpoint of the arrow. TODO: Find better solution for various font sizes
				DrawTriangle(
					{ TrianglePosition.x,  TrianglePosition.y - 8 },
					{ TrianglePosition.x, TrianglePosition.y + 8 },
					{ TrianglePosition.x + 16, TrianglePosition.y },
					BLACK);
			}

			// How many values can we fit before we have to replace them with ellipsis?
			// The + 4 on the OffsetX gives some space after the pointer
			DrawText(Option.GetLabel().c_str(), OffsetX + 4, OffsetY, MenuTextAttributes.TextSize, MenuTextAttributes.TextColor);


			OffsetY += VerticalOffsetIncrement;
		}
	}
}
