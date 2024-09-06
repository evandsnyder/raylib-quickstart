#include "raylib.h"
#include "raymath.h"

#include "DialogBox.hpp"
#include "GameConfiguration.hpp"
#include "Menu.hpp"
#include "MenuOption.hpp"
#include "TiledMap.hpp"

#include <fmt/core.h>

using namespace vertex;

class Character
{
public:
	Character()
	{
		Position = { Configuration::Get().GetScreenWidth() / 2.0f, Configuration::Get().GetScreenHeight() / 2.0f };

		Camera.target = { Position.x + 20.0f, Position.y + 20.0f };
		Camera.offset = Position;
		Camera.zoom = 2.0f;
		Camera.rotation = 0.0f;

		// We're going to go with default files for now
		// In the future, we can worry about Making them dynamic/loadable
		IdleSpriteSheet = LoadTexture("assets/Sunnyside_World_Assets/Characters/Human/IDLE/base_idle_strip9.png");
		UpdateActiveSpriteSheet(IdleSpriteSheet, IdleSpriteCount);
		WalkingSpriteSheet = LoadTexture("assets/Sunnyside_World_Assets/Characters/Human/WALKING/base_walk_strip8.png");
	}
	~Character()
	{
		UnloadTexture(IdleSpriteSheet);
		UnloadTexture(WalkingSpriteSheet);
	}

	const Camera2D& GetCamera() const
	{
		return Camera;
	}


	void Tick()
	{
		Velocity = { 0.0f, 0.0f }; // TODO: Make this better? I don't like reconstructing each frame...

		if (IsKeyDown(KEY_W))
		{
			Velocity.y = -1.0f;
		}
		if (IsKeyDown(KEY_A))
		{
			Velocity.x = -1.0f;
		}
		if (IsKeyDown(KEY_S))
		{
			Velocity.y = 1.0f;
		}
		if (IsKeyDown(KEY_D))
		{
			Velocity.x = 1.0f;
		}

		if (IsMoving())
		{
			UpdateActiveSpriteSheet(WalkingSpriteSheet, WalkingSpriteCount);
		}
		else
		{
			UpdateActiveSpriteSheet(IdleSpriteSheet, IdleSpriteCount);
		}

		// Update Sprite direction
		// if it is 0.0f, we don't need to bother changing the sprite direction
		if ((Velocity.x < 0.0f && SpriteFrame.width > 0.0f) || (Velocity.x > 0.0f && SpriteFrame.width < 0.0f))
		{
			fmt::println("Changing Direction");
			SpriteFrame.width *= -1;
		}


		// Update the position
		// Normalize the Velocity vector to prevent fast movement...
		Velocity = Vector2Normalize(Velocity);
		Position = Vector2Add(Position, Vector2Scale(Velocity, MovementSpeed * GetFrameTime()));

		FrameCounter++;
		if (FrameCounter > 60 / FrameSpeed)
		{
			FrameCounter = 0;
			CurrentFrame = (CurrentFrame + 1) % ActiveSpriteSheetCount;
		}

		SpriteFrame.x = static_cast<float>(CurrentFrame) * static_cast<float>(ActiveSpriteSheet->width) / ActiveSpriteSheetCount;

		Camera.target = { Position.x + 20, Position.y + 20 };
	}

	void Draw()
	{
		if (ActiveSpriteSheet != nullptr)
		{
			DrawTextureRec(*ActiveSpriteSheet, SpriteFrame, Position, WHITE);
		}


		DrawText(fmt::format("Player Position: ({},{})", Position.x, Position.y).c_str(), 20, 20, 10, MAROON);
	}

	bool IsMoving() const
	{
		return Velocity.x != 0.0f || Velocity.y != 0.0f;
	}

private:
	void UpdateActiveSpriteSheet(Texture2D& NewSpriteSheet, int SpriteCount)
	{
		// No need to do anything...
		if (ActiveSpriteSheet == &NewSpriteSheet) return;

		ActiveSpriteSheet = &NewSpriteSheet;
		ActiveSpriteSheetCount = SpriteCount;
		const auto NegateWidth = SpriteFrame.width < 0.0f;
		SpriteFrame = Rectangle{ 0.0f, 0.0f, static_cast<float>(ActiveSpriteSheet->width) / ActiveSpriteSheetCount, static_cast<float>(NewSpriteSheet.height) };
		if (NegateWidth)
		{
			SpriteFrame.width *= -1;
		}

		FrameCounter = 0;
		CurrentFrame = 0;
	}

	Vector2 Position{ 0.f,0.f };
	Vector2 Velocity{ 0.0f, 0.0f };
	float MovementSpeed = 60.0f; // units/s???
	Camera2D Camera{ 0 };

	Texture2D IdleSpriteSheet;
	int IdleSpriteCount = 9;
	Texture2D WalkingSpriteSheet;
	int WalkingSpriteCount = 8;

	Texture2D* ActiveSpriteSheet = nullptr;
	int ActiveSpriteSheetCount = 9; // Default to the Idle count...
	int CurrentFrame = 0;

	int FrameSpeed = 8;
	int FrameCounter = 0;

	Rectangle SpriteFrame{ 0.0f, 0.0f, 0.0f,64.0f };

	// TODO: Can we do a character builder and then write the character to a texture??
};

Menu CreatePauseMenu()
{
	Menu PauseMenu(25.0f, 25.0f, 200.0f, Configuration::Get().GetScreenHeight() * 0.5f);
	PauseMenu.SetBackgroundColor(WHITE);

	PauseMenu.AddMenuOption(MenuOption("Option 1"));
	PauseMenu.AddMenuOption(MenuOption("Option 2"));
	PauseMenu.AddMenuOption(MenuOption("Option 3"));

	return PauseMenu;
}

int main(int argc, char** argv)
{
	int ScreenWidth = Configuration::Get().GetScreenWidth();
	int ScreenHeight = Configuration::Get().GetScreenHeight();
	InitWindow(ScreenWidth, ScreenHeight, "Hello, game programming!");

	SetExitKey(KEY_F4);
	SetTargetFPS(60);

	DialogBox Dialog(25.0f, ScreenHeight * 0.6f, ScreenWidth - 50.0f, ScreenHeight / 3);
	Dialog.SetText("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna "		  \
		"aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure"	  \
		" dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident," \
		" sunt in culpa qui officia deserunt mollit anim id est laborum.");

	auto PauseMenu = CreatePauseMenu();

	auto const* dir = GetDirectoryPath(argv[0]);
	if (!ChangeDirectory(dir))
	{
		return -1;
	}
	TiledMap Map("assets/sample.json");

	Character Player;

	bool Paused = false;
	while (!WindowShouldClose())
	{
		// Need to do some Input Mapping...
		if (IsKeyPressed(KEY_ESCAPE))
		{
			Paused = !Paused;
		}

		// Turn this into
		/*
		 * for(auto* Actor : Actors){
		 *	Actor->Tick();
		 * }
		 */
		Player.Tick();



		BeginDrawing();
		ClearBackground(RAYWHITE);

		if (Paused)
		{
			PauseMenu.Draw();
		}

		// Eventually, turn this into
		/*
		 * for(auto* Actor: Actors){
		 *	Actor->Draw()/Render();
		 * }
		 */

		BeginMode2D(Player.GetCamera());
		Map.Draw(0, 0, WHITE);
		Player.Draw();
		EndMode2D();

		DrawFPS(GetScreenWidth() - 150, 40);
		// Dialog.Draw();
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
