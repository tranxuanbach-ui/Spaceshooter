#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Minion3
{
private:
    static sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f direction;
    float speed;

public:
    Minion3(const sf::Vector2f& startPos, const sf::Vector2f& dir);

    void update(float dt);
    void draw(sf::RenderWindow& window);
    bool isOffScreen(float windowWidth, float windowHeight) const;
};
