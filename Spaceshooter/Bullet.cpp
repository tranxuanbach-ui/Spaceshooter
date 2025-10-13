#include "bullet.h"

Bullet::Bullet(sf::Texture* tex, sf::Vector2f startPos) {
    texture = tex;
    sprite.setTexture(*texture);
    sprite.setOrigin(17.5f, 10.f);  // tâm giữa viên đạn
    sprite.setPosition(startPos);
    sprite.setRotation(-90.f);      // xoay dọc hướng lên
    speed = 600.f;
}

void Bullet::update(float deltaTime) {
    sprite.move(0.f, -speed * deltaTime);
}

void Bullet::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

bool Bullet::isOffScreen() const {
    return sprite.getPosition().y < -20.f;
}
