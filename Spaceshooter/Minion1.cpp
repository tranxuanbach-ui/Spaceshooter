#include "Minion1.h"
#include <iostream>

// Định nghĩa biến static khai báo trong lớp Minion1
sf::Texture Minion1::texture;

Minion1::Minion1(const sf::Vector2f& startPos)
{
    if (texture.getSize().x == 0) // chỉ load 1 lần duy nhất
    {
        if (!texture.loadFromFile("Sprites/Enemies/Minion1.png"))
            std::cout << "Failed to load Minion1.png\n";
    }

    sprite.setTexture(texture);
	sprite.setPosition(startPos);   // đặt vị trí ban đầu
	sprite.setRotation(-180.f);     // quay ngược con minion để nó hướng xuống dưới
	speed = 300.f;                  //tốc độ của con minion1

	hp = 5;
	markedForDelete = false;
}

void Minion1::update(float dt)
{
	sprite.move(0.f, speed * dt);           // di chuyển xuống dưới
}

void Minion1::draw(sf::RenderWindow& window)
{
	window.draw(sprite);                // vẽ con minion lên cửa sổ
}

bool Minion1::takeDamage(int dmg) {
    hp -= dmg;
    return hp <= 0;
}

sf::FloatRect Minion1::getBounds() const {
    return sprite.getGlobalBounds();
}

sf::Vector2f Minion1::getPosition() const {
    return sprite.getPosition();
}

bool Minion1::isMarkedForDelete() const {
    return markedForDelete;
}

void Minion1::markForDelete() {
    markedForDelete = true;
}

bool Minion1::isOffScreen(float windowHeight) const
{
	return sprite.getPosition().y > windowHeight;       // kiểm tra nếu con minion bay ra khỏi
}
