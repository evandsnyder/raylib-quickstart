#include "raylib.h"

#include "dialogbox.hpp"

constexpr int screenWidth = 800;
constexpr int screenHeight = 450;

using namespace vertex;

int main()
{
	InitWindow(screenWidth, screenHeight, "Hello, game programming!");
	SetTargetFPS(60);

	DialogBox dialog;

	while(!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("Hello, game development!", 190, 200, 20, LIGHTGRAY);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
