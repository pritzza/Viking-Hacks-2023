#pragma once

#include <SFML/Graphics.hpp>

struct Stage;

struct Entity
{
    Entity(
        const sf::Vector2f& pos,
        const sf::Vector2f& dim,
        const sf::Color& outline,
        const sf::Color& fill
    );

    void update(float dt, Stage& s);
    void draw(sf::RenderWindow& window);
    void move(const sf::Vector2f& v);

    sf::RectangleShape box;

    sf::Vector2f pos;
    sf::Vector2f vel{ 0,0 };
    sf::Vector2f dim;
    sf::Vector2f acceleration{ 0, 0 };

    bool hasGravity{ false };

    float speed{ 50 };

    void jump(int height);
};