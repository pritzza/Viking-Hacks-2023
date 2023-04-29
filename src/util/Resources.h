#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

struct Resources
{
	sf::Texture grassTileTexture;
	sf::Texture dirtTileTexture;

	sf::Texture vikingTexture;

	sf::Font textFont;

	Resources()
	{
		grassTileTexture.loadFromFile("res/grass_burn.png");
		dirtTileTexture.loadFromFile("res/dirt.png");

		vikingTexture.loadFromFile("res/viking.png");

		textFont.loadFromFile("C:/Windows/Fonts/Calibri.ttf");
	}
};