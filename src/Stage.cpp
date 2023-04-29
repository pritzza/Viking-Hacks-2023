#include "Stage.h"

#include <SFML/Graphics.hpp>

Stage::Stage(int width, int height)
	:
	width{ width },
	height{ height },
	size{ width*height },
	tiles{ width*height }
{
	for (int i = 0; i < size; ++i)
	{
		int x = i % width;
		int y = i / width;

		if (y == height - 5 && x > 8)
			tiles[i].exists = true;

		if (y == height - 3 && x == 4)
			tiles[i].exists = true;

		if (y == height-2)
			tiles[i].exists = true;
	}
}

void Stage::draw(sf::RenderWindow& w)
{
	static sf::RectangleShape tile;
	tile.setSize({ Tile::LENGTH, Tile::LENGTH });
	tile.setFillColor(sf::Color::Green);
	tile.setOutlineThickness(1);
	tile.setOutlineColor(sf::Color::White);

<<<<<<< HEAD
	const sf::Vector2f tileSpriteScale = { Tile::LENGTH / 12.f, Tile::LENGTH / 12.f };
	sprite.setScale(tileSpriteScale);

=======
	
	const sf::Vector2f tileSpriteScale = { Tile::LENGTH/12.f, Tile::LENGTH/12.f };
	tileSprite.setScale(tileSpriteScale);

	//w.draw(tileSprite);
>>>>>>> c8c3cd871c8bd6987aabadf4a7f74c2550d8401a
	for (int i = 0; i < size; ++i)
	{
		int x = i % width;
		int y = i / width;
		const sf::Vector2i pos{ x, y };

		if (tiles[i].exists)
		{
<<<<<<< HEAD
			tile.setPosition(sf::Vector2f{ pos * Tile::LENGTH });
			w.draw(tile);
			sprite.setPosition(sf::Vector2f{ pos * Tile::LENGTH });
			w.draw(sprite);
=======
			tileSprite.setPosition(sf::Vector2f{ pos * Tile::LENGTH });
			w.draw(tileSprite);
>>>>>>> c8c3cd871c8bd6987aabadf4a7f74c2550d8401a
		}
	}

}
