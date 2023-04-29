#pragma once

#include <vector>

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

	sf::Sprite sprite;
	
	void draw(sf::RenderWindow& w);
};