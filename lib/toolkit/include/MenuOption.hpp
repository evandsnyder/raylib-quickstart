#ifndef VERTEX_MENU_OPTION_HPP
#define VERTEX_MENU_OPTION_HPP

#include <string>

namespace vertex {
	class MenuOption {
	public:
		MenuOption(std::string Label);

		void SetLabel(const std::string& NewLabel);
		const std::string& GetLabel() const;

	private:
		friend class Menu;

		std::string Label;
	};
}

#endif
