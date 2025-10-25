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

    bool markedForDelete = false;
    bool isMarkedForDelete() const { return markedForDelete; }
    void markForDelete() { markedForDelete = true; }

    sf::FloatRect getBounds() const { return sprite.getGlobalBounds(); }

    sf::Vector2f getPosition() const;
};
