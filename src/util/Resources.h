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
	sf::Texture evilcorpEmployeeTexture;

	// projectiles
	sf::Texture flowerProjectileTexture;

	// backgrounds
	sf::Texture forestBackgroundTexture;
	sf::Texture waterBackgroundTexture;
	sf::Texture waterBackgroundPoisonTexture;


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
		evilcorpEmployeeTexture.loadFromFile("res/evilcorp_employee.png");

		flowerProjectileTexture.loadFromFile("res/flower_projectile.png");

		forestBackgroundTexture.loadFromFile("res/forest_background.png");
		waterBackgroundTexture.loadFromFile("res/water_background.png");
		waterBackgroundPoisonTexture.loadFromFile("res/water_background_poison.png");

		textFont.loadFromFile("C:/Windows/Fonts/Calibri.ttf");
	}
};