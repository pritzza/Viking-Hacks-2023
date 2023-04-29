#include "Entity.h"

#include "Stage.h"
#include "util/AABB.h"

#include <iostream>

Entity::Entity(
    const sf::Vector2f& pos,
    const sf::Vector2f& dim,
    const sf::Color& outline,
    const sf::Color& fill
)
    :
    pos{ pos },
    dim{ dim }
{
    //box.setSize(sf::Vector2f(dim));
    //box.setFillColor(fill);
    //box.setOutlineColor(outline);
    //box.setOutlineThickness(1.f);

}

void Entity::update(float dt, Stage& s)
{
    if (hasGravity)
        acceleration.y += 1;

    acceleration *= 0.9f;

    constexpr float MIN_ACCELERATION{ 0.1f };

    if (abs(acceleration.x) < MIN_ACCELERATION)
        acceleration.x = 0;
    if (abs(acceleration.y) < MIN_ACCELERATION)
        acceleration.y = 0;

    vel += acceleration;

    for (int i = 0; i < s.tiles.size(); ++i)
    {
        if (s.tiles[i].exists)
        {
            int x = i % s.width;
            int y = i / s.width;

            AABB tile{ x * Tile::LENGTH, y * Tile::LENGTH, Tile::LENGTH, Tile::LENGTH };
            AABB entityNextX{ pos.x + vel.x, pos.y,         dim.x, dim.y };
            AABB entityNextY{ pos.x,         pos.y + vel.y, dim.x, dim.y };

            const bool verticalCollision{ collide(entityNextY, tile) };
            const bool horizontalCollision{ collide(entityNextX, tile) };

            if (verticalCollision)
            {
                const bool isUp{ vel.y < 0 };

                if (isUp)
                    pos.y = tile.bottom();
                else
                    pos.y = tile.top() - dim.y;

                vel.y = 0;
            }

            if (horizontalCollision)
            {
                const bool isLeft{ vel.x < 0 };
            
                if (isLeft)
                    pos.x = tile.right();
                else
                    pos.x = tile.left() - dim.x;
            
                vel.x = 0;
            }
        }
    }


    pos += vel * dt * speed;
    vel = { 0, 0 };

    box.setPosition(sf::Vector2f(pos));
    //
    sprite.setPosition(sf::Vector2f(pos));
}

void Entity::draw(sf::RenderWindow& window)
{
    window.draw(box);

    window.draw(sprite);
}

void Entity::move(const sf::Vector2f& f)
{
    acceleration += f;
}

void Entity::jump(int height)
{
    acceleration.y = -height;
}
