#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Bullet.h"

class Player {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Texture bulletTexture;
    float frameDelay, frameTimer;
    int currentFrame;
    sf::Vector2f velocity;
    bool movingLeft, movingRight, returningLeft, returningRight;
    std::vector<sf::IntRect> frames;

    float shootDelay, shootTimer;
    std::vector<Bullet> bullets;

    sf::Vector2u windowSize;
    sf::Vector2f startPosition;

public:
    Player(const sf::Vector2u& windowSize);
    void handleInput();
    void update(float deltaTime);           
    void draw(sf::RenderWindow& window);
	const std::vector<Bullet>& getBullets() const { return bullets; }   // chỉ cho phép đọc đạn
	std::vector<Bullet>& getBullets() { return bullets; }               // cho phép sửa đổi đạn

    sf::FloatRect getBounds() const { return sprite.getGlobalBounds(); }
    bool markedForDelete = false;
    void markForDelete() { markedForDelete = true; }
    bool isMarkedForDelete() const { return markedForDelete; }
};
