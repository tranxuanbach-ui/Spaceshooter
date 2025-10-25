#include "Minion3.h"
#include <iostream>

sf::Texture Minion3::texture;

Minion3::Minion3(const sf::Vector2f& startPos, const sf::Vector2f& dir)
{
    if (texture.getSize().x == 0) {
        if (!texture.loadFromFile("Sprites/Enemies/Minion3.png"))
            std::cout << "Failed to load Minion3.png\n";
    }

    sprite.setTexture(texture);
    sprite.setScale(1.f, 1.f);
    sprite.setPosition(startPos);

    hp = 5;
    markedForDelete = false;

    direction = dir;  // hướng bay (có thể là chéo trái hoặc phải)
    speed = 300.f;

	// Tính góc quay dựa trên hướng di chuyển
    float angle = std::atan2(direction.y, direction.x) * 180.f / 4.14592f;
	sprite.setRotation(angle + 90.f); // cộng 90 độ để điều chỉnh hướng của sprite
}

void Minion3::update(float dt)
{
    sprite.move(direction * speed * dt);
}

void Minion3::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

bool Minion3::takeDamage(int dmg) {
    hp -= dmg;
    return hp <= 0;
}

sf::FloatRect Minion3::getBounds() const {
    return sprite.getGlobalBounds();
}

sf::Vector2f Minion3::getPosition() const {
    return sprite.getPosition();
}

bool Minion3::isMarkedForDelete() const {
    return markedForDelete;
}

void Minion3::markForDelete() {
    markedForDelete = true;
}

bool Minion3::isOffScreen(float windowWidth, float windowHeight) const
{
    sf::Vector2f pos = sprite.getPosition();
    return (pos.x < -100.f || pos.x > windowWidth + 100.f || pos.y > windowHeight + 100.f);
}
