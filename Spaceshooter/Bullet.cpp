#include"Bullet.h"

Bullet::Bullet(sf::Texture * tex, sf::Vector2f startPos) {
    texture = tex;
    sprite.setTexture(*texture);
    sprite.setOrigin(17.5f, 10.f);  // tâm giữa viên đạn
    sprite.setPosition(startPos);
    sprite.setRotation(-90.f);      // xoay dọc hướng lên
    speed = 600.f;
}

void Bullet::update(float deltaTime) {
	sprite.move(0.f, -speed * deltaTime);       // di chuyển viên đạn của player lên trên
}

void Bullet::draw(sf::RenderWindow& window) {
	window.draw(sprite);                        // vẽ viên đạn lên cửa sổ
}

bool Bullet::isOffScreen() const {
	return sprite.getPosition().y < -20.f;      //kiểm tra nếu đạn bay ra khỏi cửa sổ window
}