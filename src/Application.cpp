#include "Application.h"

#include <iostream>

#include <algorithm>
#include <iomanip>
#include <functional>
#include <math.h>

enum class ButtonState
{
	Idle,
	Pressed,
	Held,
	Released,
};

static ButtonState buttonStates[sf::Keyboard::KeyCount] = { ButtonState::Idle };

void updateButtonState(const sf::Keyboard::Key keyID)
{
	ButtonState& buttonState{ buttonStates[keyID] };

	if (sf::Keyboard::isKeyPressed(keyID))
	{
		switch (buttonState)
		{
		case ButtonState::Idle:
			buttonState = ButtonState::Pressed;
			break;
		case ButtonState::Pressed:
			buttonState = ButtonState::Held;
			break;
		}
	}
	else
	{
		switch (buttonState)
		{
		case ButtonState::Held:
		case ButtonState::Pressed:
			buttonState = ButtonState::Released;
			break;
		case ButtonState::Released:
			buttonState = ButtonState::Idle;
			break;
		}
	}
}

Application::Application(const uint16_t width, const uint16_t height, const uint8_t frameRate, const std::string& name)
	:
	m_window{ width, height, name },
	m_frameRate{ frameRate }
{
	this->init();
}

void Application::init()
{
	Tile::init();

	Entity e{ { 100,100 }, { 50,50 }, sf::Color::White, sf::Color::Red };

	for (int i = 0; i < 3; ++i)
	{
		e.pos = sf::Vector2f{ (i * 100.f) + 100.f, 100.f };
		e.type = EntityType::Enemy;
		entities.push_back(e);

		entities.back().hasGravity = true;
	}

	// adding entities
	Entity vine{ createVine({ 100, 100 }, { 25, 300 }, res) };
	entities.push_back(vine);

	Entity tree{ createDeadTree({500, 100}, {32, 160}, res) };
	entities.push_back(tree);

	Entity badGuy1{ createBadGuy({800, 100}, res) };
	entities.push_back(badGuy1);

	Entity badGuy2{ createBadGuy({300, 100}, res) };
	entities.push_back(badGuy2);

	Entity badGuy3{ createBadGuy({2300, 100}, res) };
	entities.push_back(badGuy3);

	// cutscene
	std::vector<std::string> lines{ "Hello World!", "Blah Blah Blah", "Does this work?" };
	Cutscene* scene = new Cutscene{ lines };
	scene->spotlight = &entities[2];
	scene->init(res);

	cutscene = scene;
}

void Application::start()
{
	m_isRunning = true;

	this->applicationLoop();
}

void Application::stop()
{
	m_isRunning = false;
}

void Application::applicationLoop()
{
	static sf::Clock timer;

	const int TARGET_FPS{ 60 };
	const double TARGET_FRAME_LENGTH{ 1.0 / TARGET_FPS };

	sf::Time currentFrameStart;
	sf::Time prevFrameStart;
	sf::Time nextFrameStart;

	double deviation{};

	while (m_isRunning)
	{
		// timing stuff
		prevFrameStart = currentFrameStart;
		currentFrameStart = timer.getElapsedTime();
		sf::Time dt{ currentFrameStart - prevFrameStart };

		static const sf::Time MIN_DT{ sf::seconds(1.0 / 240.0) }; // fastest a frame could reasonably be
		static const sf::Time MAX_DT{ sf::seconds(1.0 / 30.0) };  // slowest a frame could reasonably be

		dt = sf::seconds(
			std::clamp(dt.asSeconds(), MIN_DT.asSeconds(), MAX_DT.asSeconds()
		));

		if (frame > 60)
			deviation += dt.asSeconds() - TARGET_FRAME_LENGTH;

		// frame debugging
		static constexpr bool FRAME_DEBUGGING{ true };
		if constexpr (FRAME_DEBUGGING)
			if (frame % TARGET_FPS == 0)
			{
				std::cout << "Cur Time: " << currentFrameStart.asMicroseconds() << '\n';
				std::cout << "Avg Frame Dev: " << deviation / frame << '\n';
				std::cout << "DT: " << dt.asSeconds() << '\n';
				std::cout << "DT Error: " << dt.asSeconds() - TARGET_FRAME_LENGTH << '\n';
				std::cout << std::endl;
			}

		// main loop
		this->handleInput();
		this->update(dt.asSeconds());
		this->render();

		// timing stuff again
		frame++;
		nextFrameStart = sf::seconds(frame * TARGET_FRAME_LENGTH);

		while (timer.getElapsedTime() < nextFrameStart)
		{
			// spin lock
		}
	}
}

void Application::handleInput()
{
    // input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        player.move({ 0,-1 });
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        player.move({ -1,0 });
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        player.move({ 0,1 });
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        player.move({ 1,0 });

	if (buttonStates[sf::Keyboard::Space] == ButtonState::Pressed)
		player.jump(20);

	if (buttonStates[sf::Keyboard::Q] == ButtonState::Pressed)
		player.pos = { 200, 0 };
	
	if (buttonStates[sf::Keyboard::P] == ButtonState::Pressed)
	{
		Entity projectile = createProjectile(
			player,
			{ EntityType::Enemy },
			30,
			false,
			0.2,
			player.direction,
			{ 20,20 },
			sf::Color::White,
			sf::Color::Green,
			{ CollisionResponse::Disappear },	// self
			{ CollisionResponse::Hurt },		// other
			{ CollisionResponse::Disappear }	// tile
		);

		entities.push_back(projectile);
	}

	if (buttonStates[sf::Keyboard::E] == ButtonState::Pressed)
	{
		if (cutscene)
			cutscene->nextLine();
	}
}

void Application::update(float dt)
{
	m_window.update();

	const bool windowClosed{ !m_window.getWindow().isOpen() };
	if (windowClosed)
	{
		m_isRunning = false;
		return;
	}

	// need to update state of every key in use
	updateButtonState(sf::Keyboard::Space);
	updateButtonState(sf::Keyboard::E);
	updateButtonState(sf::Keyboard::Q);
	updateButtonState(sf::Keyboard::P);

    player.update(dt, stage, entities);

	for (int i = 0; i < entities.size(); ++i)
	{
		Entity& e{ entities[i] };

		e.update(dt, stage, entities);
	}

	constexpr float PARALLAX_STRENGTH{ 1.5f };
	sf::Vector2f stageDim(stage.background.getTexture()->getSize() / 2u);
	stage.background.setPosition((player.pos / PARALLAX_STRENGTH) - stageDim);

	if (cutscene)
	{
		cutscene->update(dt);

		if (cutscene->isOver)
		{
			delete cutscene;
			cutscene = nullptr;
		}
	}
}

void Application::render()
{
    sf::RenderWindow& window{ m_window.getWindow() };

	view.setCenter(player.pos + (player.dim/2.f));
	view.setSize({ 600,400 });
	window.setView(view);

    window.clear();

	window.draw(stage.background);

	for (Entity& e : entities)
		e.draw(window);

	stage.draw(window, res);

	player.draw(window);

	if (cutscene)
		cutscene->draw(window, view);

    window.display();
}