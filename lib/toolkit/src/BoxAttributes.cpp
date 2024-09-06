#include "BoxAttributes.hpp"

namespace vertex
{
	BoxAttributes::BoxAttributes(float PositionX, float PositionY, float Width, float Height)
		: Rect(PositionX, PositionY, Width, Height)
	{
	}

	void DrawBox(const BoxAttributes& Attributes)
	{
		DrawRectangleRec(Attributes.Rect, Attributes.BackgroundColor);

		if (Attributes.BorderThickness > BORDER_NONE)
		{
			DrawRectangleLinesEx(Attributes.Rect, Attributes.BorderThickness, Attributes.BorderColor);
		}
	}
}
