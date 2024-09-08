#include "Toolkit.hpp"

#include "raylib.h"

namespace vertex
{
	void CreateGameWindow(int WindowWidth, int WindowHeight, const std::string& GameTitle)
	{
		InitWindow(WindowWidth, WindowHeight, GameTitle.c_str());
		SetTargetFPS(60);
	}
}
