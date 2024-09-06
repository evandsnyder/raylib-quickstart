#ifndef VERTEX_LEVEL_HPP
#define VERTEX_LEVEL_HPP

#include "raylib-tileson.h"

namespace vertex {
	class Level {
	public:
		Level();
		~Level();


		void Draw();

	private:

		Map LevelMap;
	};
}

#endif
