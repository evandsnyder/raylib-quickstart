#include "gameconfiguration.hpp"

namespace vertex
{
	Configuration& Configuration::Get()
	{
		static Configuration instance;

		return instance;
	}

	void Configuration::SetScreenWidth(float NewScreenWidth)
	{
		ScreenWidth = NewScreenWidth;
	}

	float Configuration::GetScreenWidth() const
	{
		return ScreenWidth;
	}

	void Configuration::SetScreenHeight(float NewScreenHeight)
	{
		ScreenHeight = NewScreenHeight;
	}

	float Configuration::GetScreenHeight() const
	{
		return ScreenHeight;
	}

	Configuration::Configuration()
	{
	}
}
