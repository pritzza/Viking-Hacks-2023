#pragma once

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

struct Resources;

struct Tile
{
	enum class Graphic
	{
		Empty,
		Grass,
		Dirt,
	};

	static constexpr int LENGTH{ 32 };

	Graphic graphic{ Graphic::Empty };
	bool isSolid{ false };
	bool isAttacking{ false };

	inline static sf::RectangleShape boundingBox;
	inline static sf::Sprite sprite;

	Tile(Graphic g, bool isSolid, bool isAttacking);

	static void init();

	void draw(sf::RenderWindow& window, Resources& res, const sf::Vector2i& pos) const;
};

struct Stage
{
public:
	Stage(int width, int height, const std::string& data);

	inline static const Tile grassTile{ Tile::Graphic::Grass,	true,	false };
	inline static const Tile emptyTile{ Tile::Graphic::Empty,	false,	false };
	inline static const Tile dirtTile{  Tile::Graphic::Dirt,	true,	false };

	std::vector<const Tile*> tiles;

	int width;
	int height;
	int size;

	sf::Sprite sprite;
	
	void draw(sf::RenderWindow& w, Resources& res);
};