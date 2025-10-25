#pragma once
#include<SFML/Graphics.hpp>

class Minion1 {
private:
	static sf::Texture texture; // static -> dùng chung cho tất cả các đối tượng là Minion1
    sf::Sprite sprite;
    float speed;
	int hp;         // điểm máu của Minion1
	bool markedForDelete = false; // đánh dấu để xóa Minion1 khi bị tiêu diệt

public:
    Minion1(const sf::Vector2f& startPos);
    void update(float dt);
    void draw(sf::RenderWindow& window);
    bool isOffScreen(float windowHeight) const;

    bool takeDamage(int dmg);
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;

    bool isMarkedForDelete() const;
    void markForDelete();
};
