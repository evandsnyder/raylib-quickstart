#include "raylib.h"

constexpr int screenWidth = 800;
constexpr int screenHeight = 450;

int main()
{
	InitWindow(screenWidth, screenHeight, "Hello, game programming!");
	SetTargetFPS(60);

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
