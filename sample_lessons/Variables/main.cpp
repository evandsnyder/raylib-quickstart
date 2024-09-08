#include "raylib.h"

#include "DialogBox.hpp"
#include "Toolkit.hpp"

using namespace vertex;

int main(int argc, char** argv)
{
	/* These are variables, little containers that we can store data in
	 * They're useful for lots of stuff!
	 *
	 * In the Hello, World example, we had to write the values of 800 and 450
	 * anytime we wanted to talk about the dimensions of the screen space.
	 * This can get tedious because we might want to change the screen size later
	 * such as when a user resizes the window
	 *
	 * A Variable lets us store the value of something in a little box and then read or modify it later
	 *
	 * In this example, we store the screen width and height into a variable, and we're able to use it to
	 * control not only the game window but also the size of the dialog box. In the future, we modify just the variable here
	 * and the it will be reflected on both the game window and the dialog box;
	 */
	int ScreenWidth = 800;
	int ScreenHeight = 450;

	std::string GameTitle = "Hello, variables!";


	// We're re-using the Width/Height variables so that we only have to change
	// them in one place!
	CreateGameWindow(ScreenWidth, ScreenHeight, GameTitle);

	// This is also a variable! Its type is 'DialogBox' and we're calling it Dialog
	// Dialog is an Object, so it is a little bit trickier than primitives
	// Don't worry about this too much yet, we will cover it more when we talk about Object Oriented Programming
	DialogBox Dialog = DialogBox(0, 0, ScreenWidth, ScreenHeight);

	// Students can start to modify the text here in between the quotes
	std::string MyTextVariable = "Hello, today we're learning about variables!";

	// TODO: Figure out how students can make their own variables and start integrating them into the game scene


	Dialog.SetText(MyTextVariable);

	/*
	 * Using Raylib does force us into functions, boolean logic and loops
	 * immediately, there isn't a way around this (easily) so we will
	 * likely have students just ignore it for awhile.
	 *
	 * Alternatively, we try to abstract this away and hide it in a game class
	 * so students don't have to see it yet
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
