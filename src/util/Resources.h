#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

struct Resources
{
	// tiles
	sf::Texture grassTileTexture;
	sf::Texture dirtTileTexture;
	sf::Texture grassBurnTileTexture;

	// entities
	sf::Texture vikingTexture;
	sf::Texture moneyTexture;
	sf::Texture seedTexture;
	sf::Texture seedSignTexture;
	sf::Texture deadTreeTexture;
	sf::Texture vineTexture;
	sf::Texture rainDropTexture;
	sf::Texture rainDropPoisonTexture;


	// fonts
	sf::Font textFont;

	Resources()
	{
		grassTileTexture.loadFromFile("res/grass_burn.png");
		dirtTileTexture.loadFromFile("res/dirt.png");
		grassBurnTileTexture.loadFromFile("res/grass_burn.png");

		vikingTexture.loadFromFile("res/viking.png");
		moneyTexture.loadFromFile("res/money.png");
		seedTexture.loadFromFile("res/seed.png");
		seedSignTexture.loadFromFile("res/seed_sign.png");
		deadTreeTexture.loadFromFile("res/tree_dead.png");
		vineTexture.loadFromFile("res/vine.png");
		rainDropTexture.loadFromFile("res/rain_drop.png");
		rainDropPoisonTexture.loadFromFile("res/rain_drop_poison.png");

		textFont.loadFromFile("C:/Windows/Fonts/Calibri.ttf");
	}
};