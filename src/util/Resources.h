#pragma once

#include <SFML/Graphics/Texture.hpp>

struct Resources
{
	sf::Texture grassTileTexture;
	sf::Texture vikingTexture;

	Resources()
	{
		grassTileTexture.loadFromFile("res/grass.png");
		vikingTexture.loadFromFile("res/viking.png");
	}
};