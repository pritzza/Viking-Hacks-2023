#pragma once

#include <SFML/Graphics.hpp>

#include <cstdint>
#include <string>

class Window final
{
private:
	sf::RenderWindow m_renderWindow;	// the window is where we render the buffer to

	bool focused{ true };

public:
	Window(const uint16_t width, const uint16_t height, const std::string& name);

	void update();
	void clear(const sf::Color clearColor);

	sf::RenderWindow& getWindow() { return m_renderWindow; }

private:
	void pollEvents();

};