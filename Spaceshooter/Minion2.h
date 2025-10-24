#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Minion2Bullet
{
private:
    sf::Sprite sprite;
    static sf::Texture huhtexture;
    float speed;

public:
    Minion2Bullet(const sf::Vector2f& pos)
    {
        huhtexture.loadFromFile("Sprites/Enemies/EnemyBullet2.png");
        sprite.setTexture(huhtexture);
        sprite.setPosition(pos);
        sprite.setRotation(90.f);
        sprite.setScale(0.5f, 0.5f);
        speed = 500.f;
    }

    void update(float dt) { sprite.move(0.f, speed * dt); }
    void draw(sf::RenderWindow& window) { window.draw(sprite); }
    bool isOffScreen(float windowHeight) const { return sprite.getPosition().y > windowHeight; }
};

class Minion2
{
private:
    sf::Sprite sprite;
    static sf::Texture texture;
    float speed;
    bool stopped;
    float stopY;

    float shootTimer;
    float shootDelay;

public:
    std::vector<Minion2Bullet> bullets;

    Minion2(const sf::Vector2f& startPos);
    void update(float dt);
    void draw(sf::RenderWindow& window);
    bool isOffScreen(float windowHeight) const;

    sf::Vector2f getPosition() const { return sprite.getPosition(); }
};
