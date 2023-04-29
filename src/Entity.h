#pragma once

#include <SFML/Graphics.hpp>

struct Stage;

enum class CollisionResponse
{
    ResetJumps,
    Hurt,
    Solid,
};

enum class EntityType
{
    Object,
    Creature,
    Player
};

struct Entity
{
    Entity(
        const sf::Vector2f& pos,
        const sf::Vector2f& dim,
        const sf::Color& outline,
        const sf::Color& fill
    );

    void update(float dt, Stage& s, std::vector<Entity>& entities);
    void draw(sf::RenderWindow& window);
    void move(const sf::Vector2f& v);

    sf::RectangleShape box;
    sf::Sprite sprite;

    sf::Sprite sprite;

    sf::Vector2f pos;
    sf::Vector2f vel{ 0, 0 };
    sf::Vector2f dim;
    sf::Vector2f acceleration{ 0, 0 };

    CollisionResponse onCollision;

    bool hasGravity{ false };
    bool isGrounded{ false };
    int maxNumJumps{ 1 };
    int numJumpsLeft{ 0 };

    EntityType type{ EntityType::Object };

    float runSpeed{ 50 };
    float jumpSpeed{ 50 };

    void jump(int height);
};