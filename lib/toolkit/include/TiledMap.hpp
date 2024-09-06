#ifndef VERTEX_TILED_MAP_HPP
#define VERTEX_TILED_MAP_HPP

#include "tileson.hpp"
#include "raylib.h"

#include <filesystem>

namespace vertex {
	class TiledMap {
	public:
		TiledMap(std::filesystem::path MapFile);
		~TiledMap();

		void Draw(int PositionX, int PositionY, Color Tint);

	private:
		void LoadTiledFromMemory();
		void LoadTiledImage(const std::filesystem::path& BaseDirectory, const std::filesystem::path& ImagePath, tson::Colori TransparentColor);
		bool IsTiledReady() const;

		void DrawLayer(tson::Layer& Layer, int PositionX, int PositionY, Color Tint);
		void DrawObjectLayer(tson::Layer& Layer, int PositionX, int PositionY, Color Tint);
		void DrawImageLayer(tson::Layer& Layer, int PositionX, int PositionY, Color Tint);
		void DrawTileLayer(tson::Layer& Layer, int PositionX, int PositionY, Color Tint);


		int Width;
		int Height;
		int TileWidth;
		int TileHeight;

		std::map<std::string, Texture> TextureAtlas{};
		std::unique_ptr<tson::Map> Map = nullptr;
	};
}

#endif
