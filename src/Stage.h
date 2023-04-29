#pragma once

#include <vector>
#include <SFML/Graphics.hpp>S

#include <SFML/Graphics.hpp>


struct Tile
{
	static constexpr int LENGTH{ 32 };

	bool exists{false};
};

struct Stage
{
public:
	Stage(int width, int height);
	std::vector<Tile> tiles;

	int width;
	int height;
	int size;

<<<<<<< HEAD
	sf::Sprite sprite;
	
=======
	sf::Sprite tileSprite;

>>>>>>> c8c3cd871c8bd6987aabadf4a7f74c2550d8401a
	void draw(sf::RenderWindow& w);
};