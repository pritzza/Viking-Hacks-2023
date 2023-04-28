#pragma once

#include <vector>

namespace sf 
{
	class RenderWindow;
}

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

	void draw(sf::RenderWindow& w);
};