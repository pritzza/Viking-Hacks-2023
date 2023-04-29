#pragma once


#include "Cutscene.h"
#include "Entity.h"
#include "Stage.h"

#include "util/Resources.h"
#include "util/Window.h"

class Application final
{
public:
	Application(
		const uint16_t width,
		const uint16_t height, 
		const uint8_t frameRate, 
		const std::string& name
	);

	void start();
	void stop();

private:
	Window m_window;
	sf::View view;

	Resources res;

	Cutscene* cutscene{ nullptr };

	Entity player{ {0,0}, {25,50}, sf::Color::White, sf::Color::Blue };
	std::vector<Entity> entities;

	// LOOK AT CONSTRUCTOR OF Stage IN Stage.cpp FOR CHARACTER MAPPINGS
	const std::string STAGE_1_DATA{
		R"(
		..........
		..........
		....gggg..
		gggggddggg
		dddddddddd
		)"
	};

    Stage stage{ 10, 5, STAGE_1_DATA };

	int frame{};

	const uint8_t m_frameRate;

	bool m_isRunning{ false };

private:
	void init();

	void applicationLoop();

	void handleInput();
	void update(float dt);
	void render();
};