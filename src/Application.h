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

	Entity player{ {0,0}, {50,50}, sf::Color::White, sf::Color::Blue };
	std::vector<Entity> entities;

    Stage stage{ 20, 10 };

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