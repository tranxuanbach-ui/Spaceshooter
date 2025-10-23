#pragma once
#include<SFML/Graphics.hpp>

class Minion1 {
private:
	static sf::Texture texture; // static -> dùng chung cho tất cả các đối tượng là Minion1
    sf::Sprite sprite;
    float speed;
public:
    Minion1(const sf::Vector2f& startPos);
    void update(float dt);
    void draw(sf::RenderWindow& window);
    bool isOffScreen(float windowHeight) const;
};
