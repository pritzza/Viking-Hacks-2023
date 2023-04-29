<<<<<<< HEAD
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
=======
#pragma once

#include <SFML/Graphics/Texture.hpp>

struct Resources
{
	sf::Texture grassTileTexture;
	sf::Texture vikingTexture;

	Resources()
	{
		grassTileTexture.loadFromFile("res/grass.png");
		vikingTexture.loadFromFile("res/vikingCharacter.png");
	}
>>>>>>> c8c3cd871c8bd6987aabadf4a7f74c2550d8401a
};