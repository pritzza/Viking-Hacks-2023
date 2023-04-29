#include "Stage.h"

#include <SFML/Graphics.hpp>

#include <assert.h>

#include <iostream>

#include "util/Resources.h"

Stage::Stage(int width, int height, const std::string& data)
	:
	width{ width },
	height{ height },
	size{ width * height },
	tiles{ width * height }
{
	std::string parsedData;
	for (const char c : data)
	{
		if (c < 32)
			continue;
		parsedData += c;
	}

	if (size != parsedData.size())
		std::cout << "ERROR LEVEL DATA NOT SAME SIZE";

	static constexpr char GRASS{ 'g' };
	static constexpr char DIRT{ 'd' };
	static constexpr char EMPTY{ ' ' };

	for (int i = 0; i < size; ++i)
	{
		const char c{ parsedData[i] };
		const Tile* tile = &emptyTile;;

		switch (c)
		{
		case GRASS:		tile = &grassTile;	break;
		case DIRT:		tile = &dirtTile;	break;
		}

		tiles[i] = tile;
	}
}

void Stage::draw(sf::RenderWindow& window, Resources& res)
{
	for (int i = 0; i < size; ++i)
	{
		const Tile* const tile{ tiles[i] };

		if (tile->graphic != Tile::Graphic::Empty)
		{
			int x = i % width;
			int y = i / width;
			const sf::Vector2f pos{ (float)x, (float)y };

			sf::Vector2i posi(pos.x, pos.y);
			tile->draw(window, res, posi);
		}
	}
}

Tile::Tile(Graphic g, bool isSolid, bool isAttacking)
	:
	graphic{ g },
	isSolid{ isSolid },
	isAttacking{ isAttacking }
{}

void Tile::init()
{
	boundingBox.setSize({ Tile::LENGTH, Tile::LENGTH });
	boundingBox.setFillColor(sf::Color::Green);
	boundingBox.setOutlineThickness(1);
	boundingBox.setOutlineColor(sf::Color::White);

	static const sf::Vector2f spriteScale = { 2.f, 2.f };
	sprite.setScale(spriteScale);
}

void Tile::draw(sf::RenderWindow& window, Resources& res, const sf::Vector2i& pos) const
{
	sf::Texture* texture{ nullptr };

	switch (graphic)
	{
	case Graphic::Dirt:		texture = &res.dirtTileTexture;			break;
	case Graphic::Grass:	texture = &res.grassTileTexture;		break;
	default:
		texture = &res.dirtTileTexture;
	}

	sprite.setTexture(*texture);

	boundingBox.setPosition(sf::Vector2f{ pos * LENGTH });
	window.draw(boundingBox);

	sprite.setPosition(sf::Vector2f{ pos * LENGTH });
	window.draw(sprite);
}