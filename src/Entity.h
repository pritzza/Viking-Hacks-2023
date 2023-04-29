#pragma once

#include <SFML/Graphics.hpp>

struct Stage;

struct Resources;

enum class CollisionResponse
{
    Nothing,
    ResetJumps,
    Hurt,
    Stop,
    Disappear,
};

enum class EntityType
{
    Object,
    Creature,
    Enemy,
    Player
};

enum class EntityID
{
    Null,
    Player,
    BadGuy,
    Tree,
    Vine,
    Seeds,
    Cloud,
    Projectile
};

struct Entity
{
    //JUSTIN VARIABLES TO CHANGE LIKE SPEED AND STUFF
    const float playerRunSpeed =40;
    const float playerJumpSpeed = 50;

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

    sf::Vector2f pos;
    sf::Vector2f vel{ 0, 0 };
    sf::Vector2f dim;
    sf::Vector2f acceleration{ 0, 0 };
    sf::Vector2f direction{ -1, 0 };

    std::vector<EntityType> validTargets;

    std::vector<CollisionResponse> onEntityCollisionSelfResponse;
    std::vector<CollisionResponse> onEntityCollisionOtherResponse;
    std::vector<CollisionResponse> onTileCollision;

    bool shouldDespawn{ false };
    float lifetime{ 100000000000.f }; // seconds

    bool hasGravity{ false };
    bool isGrounded{ false };
    int maxNumJumps{ 1 };
    int numJumpsLeft{ 0 };

    EntityType type{ EntityType::Object };
    EntityID id{ EntityID::Null };

    float runSpeed{ playerRunSpeed };
    float jumpSpeed{ playerJumpSpeed };

    void jump(int height);

    void respond(CollisionResponse response);

};

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
    std::vector<CollisionResponse> tileHit
);

Entity createPlayer(Resources& res);

Entity createVine(
    const sf::Vector2f& pos,
    const sf::Vector2f& dim,
    Resources& res
);

Entity createDeadTree(
    const sf::Vector2f& pos,
    const sf::Vector2f& dim,
    Resources& res
);

Entity createBadGuy(
    const sf::Vector2f& pos,
    Resources& res
);

Entity createWaterDrop(
    const sf::Vector2f& pos,
    Resources& res
);

Entity createWaterDropPoison(
    const sf::Vector2f& pos,
    Resources& res
);
