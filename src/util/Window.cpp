#include "Window.h"

Window::Window(const uint16_t width, const uint16_t height, const std::string& name)
	:
	m_renderWindow{ sf::VideoMode(width, height), name, sf::Style::Default }
{}

void Window::pollEvents()
{
	sf::Event event;

	if (m_renderWindow.pollEvent(event))
		switch (event.type)
		{
		case sf::Event::Closed:			m_renderWindow.close();		break;
		case sf::Event::GainedFocus:	focused = true;				break;
		case sf::Event::LostFocus:		focused = false;			break;
		}
}

void Window::update()
{
	pollEvents();
}

void Window::clear(const sf::Color clearColor = sf::Color{ 0, 0, 0, 255 })
{
	m_renderWindow.clear(clearColor);
}