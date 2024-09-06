#include "MenuOption.hpp"

namespace vertex
{
	MenuOption::MenuOption(std::string Label)
		: Label(std::move(Label))
	{
	}

	void MenuOption::SetLabel(const std::string& NewLabel)
	{
		Label = NewLabel;
	}

	const std::string& MenuOption::GetLabel() const
	{
		return Label;
	}
}
