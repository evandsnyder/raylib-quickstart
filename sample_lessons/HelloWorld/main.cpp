#include "raylib.h"

#include "DialogBox.hpp"
#include "Toolkit.hpp"

using namespace vertex;

int main(int argc, char** argv)
{
	// Students can change start to tweak the window title
	CreateGameWindow(800, 450, "Hello, game programming");

	DialogBox Dialog = DialogBox(0, 0, 800, 450);

	// Students can start to modify the text here in between the quotes
	Dialog.SetText("Hello, welcome to game development!");

	/*
	 * Using Raylib does force us into functions, boolean logic and loops
	 * immediately, there isn't a way around this (easily) so we will
	 * likely have students just ignore it for awhile.
	 *
	 * Alternatively, we try to abstract this away and hide it in a game class
	 * so students don't have to see it yet
	 *
	 * We may want to consider how feasible it is to teach variables AND flow control in week 1
	 */
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		Dialog.Draw();
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
