#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

struct Resources
{
	sf::Texture grassTileTexture;
	sf::Texture vikingTexture;

	sf::Font textFont;

	Resources()
	{
		grassTileTexture.loadFromFile("res/grass.png");
		vikingTexture.loadFromFile("res/viking.png");

		textFont.loadFromFile("C:/Windows/Fonts/Calibri.ttf");
	}
};