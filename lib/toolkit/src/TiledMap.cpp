#include "TiledMap.hpp"

#include <ranges>
#include <fmt/core.h>

#include "MapExceptions.hpp"

namespace vertex {

	// Some Free Functions
	Color ColorFromTiledColor(const tson::Colori& TiledColor)
	{
		return { TiledColor.r, TiledColor.g, TiledColor.b, TiledColor.a };
	}

	Rectangle RectangleFromTiledRectangle(const tson::Rect& Rect)
	{
		return {
			static_cast<float>(Rect.x),
			static_cast<float>(Rect.y),
			static_cast<float>(Rect.width),
			static_cast<float>(Rect.height)
		};
	}


	// The TiledMap Class
	TiledMap::TiledMap(std::filesystem::path MapFile)
	{
		auto BaseDirectory = MapFile.parent_path();
		if (!std::filesystem::exists(MapFile))
		{
			fmt::println("Current Path is {}", std::filesystem::current_path().string());
			throw exceptions::MapNotFoundException("Map File does not exist");
		}

		tson::Tileson t;
		Map = t.parse(MapFile);

		if (!Map)
		{
			throw exceptions::MapParseException("Failed to parse map..");
			// TODO: Get Exception from map parse...
		}

		if (Map->getStatus() != tson::ParseStatus::OK)
		{
			throw exceptions::MapParseException("Failed to parse map");
		}

		// TODO: Expand to support Isometric and Hexagonal maps...
		if (Map->getOrientation() != "orthogonal")
		{
			throw exceptions::UnsupportedMapTypeException("Map is not supported map type");
		}

		for (const auto& Layer : Map->getLayers())
		{
			if (Layer.getType() == tson::LayerType::ImageLayer)
			{
				LoadTiledImage(BaseDirectory, std::filesystem::path(Layer.getImage()), Layer.getTransparentColor());
			}
		}

		for (const auto& tileset : Map->getTilesets())
		{
			LoadTiledImage(BaseDirectory, tileset.getImagePath(), tileset.getTransparentColor());
		}

		Width = Map->getSize().x;
		Height = Map->getSize().y;
		TileWidth = Map->getTileSize().x;
		TileHeight = Map->getTileSize().y;
	}

	TiledMap::~TiledMap()
	{
		if (Map)
		{
			for (const auto& Texture : TextureAtlas | std::views::values)
			{
				UnloadTexture(Texture);
			}
		}

		// TODO: Run unload logic...
	}

	void TiledMap::Draw(int PositionX, int PositionY, Color Tint)
	{
		// TODO: Log Attempting to draw null Layer...
		if (!Map) {
			fmt::println("Map is invalid");
			return;
		}

		for (auto& Layer : Map->getLayers())
		{
			DrawLayer(Layer, PositionX, PositionY, Tint);
		}
	}

	void TiledMap::LoadTiledFromMemory()
	{
	}

	void TiledMap::LoadTiledImage(const std::filesystem::path& BaseDirectory, const std::filesystem::path& ImagePath,
		tson::Colori TransparentColor)
	{
		if (TextureAtlas.contains(ImagePath.string()))
		{
			// we've already loaded this image...
			return;
		}

		auto Path = BaseDirectory / ImagePath;

		auto LoadedImage = LoadImage(Path.string().c_str());
		ImageFormat(&LoadedImage, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

		Texture ImageTexture = LoadTextureFromImage(LoadedImage);
		UnloadImage(LoadedImage);
		TextureAtlas.emplace(ImagePath.string(), ImageTexture);
	}

	bool TiledMap::IsTiledReady() const
	{
		return Map != nullptr;
	}

	void TiledMap::DrawLayer(tson::Layer& Layer, int PositionX, int PositionY, Color Tint)
	{
		switch (Layer.getType())
		{
		case tson::LayerType::TileLayer:
			DrawTileLayer(Layer, PositionX, PositionY, Tint);
			break;
		case tson::LayerType::ObjectGroup:
			DrawObjectLayer(Layer, PositionX, PositionY, Tint);
			break;
		case tson::LayerType::ImageLayer:
			DrawImageLayer(Layer, PositionX, PositionY, Tint);
			break;
		case tson::LayerType::Group:
			for (auto& NextLayer : Layer.getLayers())
			{
				DrawLayer(NextLayer, PositionX, PositionY, Tint);
			}
			break;
		default:
			// TODO: Log Unsupported Layer type...
			break;
		}
	}

	void TiledMap::DrawObjectLayer(tson::Layer& Layer, int PositionX, int PositionY, Color Tint)
	{
		auto* LayerMap = Layer.getMap();
		for (auto& Object : Layer.getObjects())
		{
			switch (Object.getObjectType())
			{
			case tson::ObjectType::Text:
			{
				if (Object.isVisible())
				{
					auto TextObject = Object.getText();
					auto const TextColor = ColorFromTiledColor(TextObject.color);
					auto const Position = Object.getPosition();
					// TODO: Font Size??
					DrawText(TextObject.text.c_str(), PositionX + Position.x, PositionY + Position.y, 16, TextColor);
				}
			}
			break;
			default:
				break;
			}
		}
	}

	void TiledMap::DrawImageLayer(tson::Layer& Layer, int PositionX, int PositionY, Color Tint)
	{
		auto& Image = Layer.getImage();
		if (!TextureAtlas.contains(Image))
		{
			return;
		}

		auto const& Texture = TextureAtlas[Image];
		auto const Offset = Layer.getOffset();
		DrawTexture(Texture, PositionX + Offset.x, PositionY + Offset.y, Tint);
	}

	void TiledMap::DrawTileLayer(tson::Layer& Layer, int PositionX, int PositionY, Color Tint)
	{
		for (auto& [Position, TileObject] : Layer.getTileObjects())
		{
			auto* Tileset = TileObject.getTile()->getTileset();
			auto Image = Tileset->getImage().string();
			if (!TextureAtlas.contains(Image))
			{
				continue;
			}

			auto& Texture = TextureAtlas[Image];
			Rectangle DrawRect = RectangleFromTiledRectangle(TileObject.getDrawingRect());
			auto Pos = TileObject.getPosition();

			DrawTextureRec(Texture, DrawRect, { Pos.x + PositionX, Pos.y + PositionY }, Tint);
		}
	}
}
