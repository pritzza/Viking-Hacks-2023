#include "Entity.h"

#include "Stage.h"
#include "util/AABB.h"
#include "util/Resources.h"

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
    box.setSize(sf::Vector2f(dim));
    box.setFillColor(fill);
    box.setOutlineColor(outline);
    box.setOutlineThickness(1.f);
}

void Entity::update(float dt, Stage& s, std::vector<Entity>& entities)
{
    if (shouldDespawn)
        return;

    lifetime -= dt;

    if (lifetime < 0)
        shouldDespawn = true;

    //physics 
    if (hasGravity)
    {
        acceleration.y += 1;
        acceleration *= 0.9f;
    }

    constexpr float MIN_ACCELERATION{ 0.1f };

    if (abs(acceleration.x) < MIN_ACCELERATION)
        acceleration.x = 0;
    if (abs(acceleration.y) < MIN_ACCELERATION)
        acceleration.y = 0;

    vel += acceleration;

    for (int i = 0; i < s.tiles.size(); ++i)
    {
        if (s.tiles[i]->isSolid)
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
                const bool isDisappearing{ 
                    std::find(
                    onTileCollision.begin(),
                    onTileCollision.end(),
                    CollisionResponse::Disappear
                    ) 
                    !=
                    onTileCollision.end() 
                };

                if (isDisappearing)
                    shouldDespawn = true;

                const bool isUp{ vel.y < 0 };

                if (isUp)
                    pos.y = tile.bottom();
                else
                {
                    pos.y = tile.top() - dim.y;

                    isGrounded = true;
                    numJumpsLeft = maxNumJumps;
                }

                vel.y = 0;
                acceleration.y = 0;
            }

            if (horizontalCollision)
            {
                const bool isDisappearing{
                    std::find(
                    onTileCollision.begin(),
                    onTileCollision.end(),
                    CollisionResponse::Disappear
                    )
                    !=
                    onTileCollision.end()
                };

                if (isDisappearing)
                    shouldDespawn = true;

                const bool isLeft{ vel.x < 0 };
            
                if (isLeft)
                    pos.x = tile.right();
                else
                    pos.x = tile.left() - dim.x;
            
                vel.x = 0;
                acceleration.x = 0;
            }
        }
    }

    pos.y += vel.y * dt * jumpSpeed;
    pos.x += vel.x * dt * runSpeed;
    vel = { 0, 0 };

    box.setPosition(sf::Vector2f(pos));
    sprite.setPosition(sf::Vector2f(pos));

    // entity-entity collision
    for (Entity& e : entities)
    {
        AABB other{ e.pos.x, e.pos.y, e.dim.x, e.dim.y };
        AABB self{ pos.x, pos.y, dim.x, dim.y };

        if (collide(self, other))
        {
            bool validCollision{ false };

            for (EntityType target : validTargets)
                if (e.type == target && this->caster != &e) // valid target and target isnt caster
                    validCollision = true;

            if (validCollision)
            {
                for (CollisionResponse selfResponse : this->onEntityCollisionSelfResponse)
                    this->respond(selfResponse);

                for (CollisionResponse otherResponse : this->onEntityCollisionOtherResponse)
                    e.respond(otherResponse);
            }
        }
    }
}

void Entity::draw(sf::RenderWindow& window)
{
    if (shouldDespawn)
        return;

    constexpr bool DRAW_BOUNDING_BOXES{ false };
    if constexpr (DRAW_BOUNDING_BOXES)
        window.draw(box);

    window.draw(sprite);
}

void Entity::move(const sf::Vector2f& f)
{
    direction = f;
    acceleration += f;
}

void Entity::jump(int height)
{
    if (numJumpsLeft > 0)
    {
        acceleration.y = -height;
        numJumpsLeft--;;
    }
}

void Entity::respond(CollisionResponse response)
{
    switch (response)
    {
    case CollisionResponse::Disappear:
        shouldDespawn = true;
        break;
    case CollisionResponse::Hurt:
            std::cout << this << ": Ouch!!!\n";
        break;
    case CollisionResponse::ResetJumps:
            numJumpsLeft = 1;
        break;
    case CollisionResponse::Stop:
        // todo
        break;

    }
}

Entity createPlayer(Resources& res)
{
    float w = 23.f;
    float h = 40.f;

    float scale{ 2.f };

    Entity player{ {0,0}, (sf::Vector2f{w,h} * scale), sf::Color::White, sf::Color::Blue };

    player.hasGravity = true;
    player.maxNumJumps = 2;
    player.type = EntityType::Player;

    player.sprite.setTexture(res.vikingTexture);

    player.sprite.setScale({ scale, scale });

    return player;
}

Entity createProjectile(
    const Entity& caster,
    std::vector<EntityType> validTargets,
    float speed,
    bool hasGravity,
    float lifetime,
    const sf::Vector2f& direction,
    const sf::Vector2f& dimensions,
    const sf::Color& fillColor,
    const sf::Color& outlineColor,
    std::vector<CollisionResponse> entityHitSelfResponse,
    std::vector<CollisionResponse> entityHitOtherResponse,
    std::vector<CollisionResponse> tileHit,
    sf::Texture& texture
)
{
    sf::Vector2f position{ (caster.pos + (caster.dim / 2.f) - (dimensions / 2.f)) };
    Entity proj{ position, dimensions, outlineColor, fillColor };

    proj.caster = &caster;

    proj.type = EntityType::Object;
    proj.id = EntityID::Projectile;

    proj.validTargets = validTargets;

    proj.acceleration = direction * speed;
    proj.hasGravity = hasGravity;

    proj.lifetime = lifetime; // no projectile should last longer than 10 seconds

    proj.onEntityCollisionSelfResponse = entityHitSelfResponse;
    proj.onEntityCollisionOtherResponse = entityHitOtherResponse;
    proj.onTileCollision = tileHit;

    proj.sprite.setTexture(texture);

    const sf::Vector2 scale{
        dimensions.x / texture.getSize().x, dimensions.y / texture.getSize().y 
    };
    proj.sprite.setScale(scale);

    return proj;
}

Entity createVine(const sf::Vector2f& pos, const sf::Vector2f& dim, Resources& res)
{
    Entity vine{ pos, dim, sf::Color::Green, sf::Color{30,180,60} };

    vine.onEntityCollisionOtherResponse = { CollisionResponse::ResetJumps };
    vine.validTargets = { EntityType::Player };
    vine.type = EntityType::Object;
    vine.id = EntityID::Vine;
    vine.hasGravity = false;

    float VINE_WIDTH{ 16.f };
    float VINE_HEIGHT{ 80.f };

    vine.sprite.setScale({ dim.x / VINE_WIDTH, dim.y / VINE_HEIGHT });

    vine.sprite.setTexture(res.vineTexture);

    return vine;
}

Entity createDeadTree(const sf::Vector2f& pos, const sf::Vector2f& dim, Resources& res)
{
    Entity tree{ pos, dim, sf::Color::Green, sf::Color{30,180,60} };

    tree.type = EntityType::Object;
    tree.id = EntityID::Tree;

    tree.hasGravity = true;

    float TREE_WIDTH{ 16.f };
    float TREE_HEIGHT{ 64.f };

    tree.sprite.setScale({ dim.x / TREE_WIDTH, dim.y / TREE_HEIGHT });

    tree.sprite.setTexture(res.deadTreeTexture);

    return tree;
}

Entity createBadGuy(const sf::Vector2f& pos, Resources& res)
{
    float w = 16;
    float h = 32;
    float scale = 2;
    sf::Vector2f dim{ w,h };

    Entity badGuy{ pos, dim* scale, sf::Color::Green, sf::Color{30,180,60} };

    badGuy.type = EntityType::Enemy;
    badGuy.id = EntityID::BadGuy;

    badGuy.onEntityCollisionOtherResponse = { CollisionResponse::Hurt };
    badGuy.onEntityCollisionSelfResponse = {};
    badGuy.hasGravity = true;


    badGuy.sprite.setScale({ scale,scale });
    badGuy.sprite.setTexture(res.evilcorpEmployeeTexture);

    return badGuy;
}
