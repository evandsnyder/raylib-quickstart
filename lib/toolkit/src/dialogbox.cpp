#include "dialogbox.hpp"

#include "gameconfiguration.hpp"

namespace vertex {
	DialogBox::DialogBox(float ScreenPositionX, float ScreenPositionY, int Width, int Height)
	{
		DialogBox(ScreenPositionX, ScreenPositionY, static_cast<float>(Width), static_cast<float>(Height));
	}

	DialogBox::DialogBox(float ScreenPositionX, float ScreenPositionY, float Width, float Height)
		: MinimumWidth(60),
		MaximumWidth(Configuration::Get().GetScreenWidth() - 50.0f),
		MinimumHeight(60),
		MaximumHeight(Configuration::Get().GetScreenHeight() - 160.0f),
		TextColor(BLACK),
		BorderColor(BLACK),
		BackgroundColor(BLUE),
		BorderRectangle(Rectangle{ ScreenPositionX, ScreenPositionY,
			std::max(MinimumWidth, std::min(MaximumWidth, Width)),
			std::max(MinimumHeight, std::min(MaximumHeight, Height)) }),
		FontSize(20.0f),
		TargetText("Enter Text")
	{
		TextFont = GetFontDefault();
	}

	void DialogBox::SetPosition(float NewPositionX, float NewPositionY) {
		BorderRectangle.x = NewPositionX;
		BorderRectangle.y = NewPositionY;
	}

	void DialogBox::SetBounds(float Width, float Height) {

		BorderRectangle.height = std::max(MinimumHeight, std::min(MaximumHeight, Height));
		BorderRectangle.width = std::max(MinimumWidth, std::min(MaximumWidth, Width));
	}

	void DialogBox::SetFont(const Font& NewFont) {
		TextFont = NewFont;
	}

	void DialogBox::SetFontSize(float NewFontSize)
	{
		FontSize = NewFontSize;
	}

	void DialogBox::SetMinimumWidth(float NewMinimumWidth)
	{
		MinimumWidth = NewMinimumWidth;
	}

	void DialogBox::SetMaximumWidth(float NewMaximumWidth)
	{
		MaximumWidth = NewMaximumWidth;
	}

	void DialogBox::SetMinimumHeight(float NewMinimumHeight)
	{
		MinimumHeight = NewMinimumHeight;
	}

	void DialogBox::SetMaximumHeight(float NewMaximumHeight)
	{
		MaximumHeight = NewMaximumHeight;
	}

	void DialogBox::SetText(const std::string& text)
	{
		TargetText = text;
	}

	void DialogBox::SetTextColor(const Color& NewColor)
	{
		TextColor = NewColor;
	}

	void DialogBox::SetBorderColor(const Color& NewColor)
	{
		BorderColor = NewColor;
	}

	void DialogBox::SetBackgroundColor(const Color& NewColor)
	{
		BackgroundColor = NewColor;
	}

	void DialogBox::SetShouldAnimateText(bool NewAnimate)
	{
		ShouldAnimateText = NewAnimate;
	}

	void DialogBox::Draw()
	{
		FrameCounter += DrawSpeed;
		DrawRectangleRec(BorderRectangle, BackgroundColor);
		DrawRectangleLinesEx(BorderRectangle, 3, BorderColor);


		Rectangle TextBox = { BorderRectangle.x + 8, BorderRectangle.y + 8, BorderRectangle.width - 8, BorderRectangle.height - 8 };

		const char* Text = ShouldAnimateText ? TextSubtext(TargetText.c_str(), 0, FrameCounter / 10) : TargetText.c_str();
		auto Length = TextLength(Text);

		float TextOffsetY = 0.0f;
		float TextOffsetX = 0.0f;
		float ScaleFactor = FontSize / static_cast<float>(TextFont.baseSize);

		enum class EWordWrap { MeasureState = 0, DrawState = 1 };
		auto DrawState = EWordWrap::MeasureState;

		int StartLine = -1;
		int EndLine = -1;
		int LastK = -1;



		for (int i = 0, k = 0; i < Length; i++, k++)
		{
			int CodepointByteCount = 0;
			int Codepoint = GetCodepoint(&Text[i], &CodepointByteCount);
			int Index = GetGlyphIndex(TextFont, Codepoint);

			if (Codepoint == 0x3f) CodepointByteCount = 1;
			i += CodepointByteCount - 1;

			float GlyphWidth = 0;
			if (Codepoint != '\n')
			{
				GlyphWidth = TextFont.glyphs[Index].advanceX == 0
					? TextFont.recs[Index].width * ScaleFactor
					: TextFont.glyphs[Index].advanceX * ScaleFactor;

				if (i + 1 < Length) GlyphWidth = GlyphWidth + GlyphSpacing;
			}

			if (DrawState == EWordWrap::MeasureState)
			{
				if (Codepoint == ' ' || Codepoint == '\t' || Codepoint == '\n') EndLine = i;

				if (TextOffsetX + GlyphWidth > TextBox.width)
				{
					EndLine = EndLine < 1 ? i : EndLine;

					if (i == EndLine) EndLine -= CodepointByteCount;

					if (StartLine + CodepointByteCount == EndLine)
						EndLine = i - CodepointByteCount;

					DrawState = EWordWrap::DrawState;
				}
				else if (i + 1 == Length)
				{
					EndLine = i;
					DrawState = EWordWrap::DrawState;
				}
				else if (Codepoint == '\n')
				{
					DrawState = EWordWrap::DrawState;
				}

				if (DrawState == EWordWrap::DrawState)
				{
					TextOffsetX = 0;
					i = StartLine;
					GlyphWidth = 0;
					int tmp = LastK;
					LastK = k - 1;
					k = tmp;
				}
			}
			else
			{
				if (Codepoint != '\n')
				{
					if (TextOffsetX + GlyphWidth > TextBox.width)
					{
						TextOffsetY += (TextFont.baseSize + TextFont.baseSize / 2) * ScaleFactor;
						TextOffsetX = 0;
					}

					if (TextOffsetY + TextFont.baseSize * ScaleFactor > TextBox.height) break;

					if (Codepoint != ' ' && Codepoint != '\t')
					{
						DrawTextCodepoint(TextFont, Codepoint, { TextBox.x + TextOffsetX, TextBox.y + TextOffsetY }, FontSize, TextColor);
					}
				}

				if (i == EndLine)
				{
					TextOffsetY += (TextFont.baseSize + TextFont.baseSize / 2) * ScaleFactor;
					TextOffsetX = 0;
					StartLine = EndLine;
					EndLine = -1;
					GlyphWidth = 0;
					k = LastK;
					DrawState = DrawState == EWordWrap::DrawState ? EWordWrap::MeasureState : EWordWrap::DrawState;
				}
			}

			if (TextOffsetX != 0 || Codepoint != ' ') TextOffsetX += GlyphWidth;
		}
	}
}
