#pragma once
#include <SFML/Graphics.hpp>

class Bullet {
private:
    sf::Sprite sprite;
    sf::Texture* texture;
    float speed;

public:
    Bullet(sf::Texture* tex, sf::Vector2f startPos);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool isOffScreen() const;
};
