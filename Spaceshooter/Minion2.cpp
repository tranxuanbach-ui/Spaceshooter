#include "Minion2.h"
#include <iostream>

sf::Texture Minion2::texture;
sf::Texture Minion2Bullet::huhtexture;

Minion2::Minion2(const sf::Vector2f& startPos)
{
    if (texture.getSize().x == 0) {
        if (!texture.loadFromFile("Sprites/Enemies/Minion2.png"))
            std::cout << "Failed to load Minion2.png\n";
    }

    sprite.setTexture(texture);
    sprite.setRotation(-180.f);
    sprite.setScale(1.f, 1.f);
    sprite.setPosition(startPos);

    speed = 200.f;
    stopY = 300.f;   // vị trí sẽ dừng lại
    stopped = false;

    shootTimer = 0.f;
    shootDelay = 1.f; // bắn mỗi 1 giây

    hp = 2;
    markedForDelete = false;
}

void Minion2::update(float dt)
{
    sf::Vector2f pos = sprite.getPosition();

    // Di chuyển xuống cho đến khi đạt stopY
    if (!stopped) {
        sprite.move(0.f, speed * dt);
        if (pos.y >= stopY)
            stopped = true;
    }
    else {
        // Khi đã dừng lại thì bắn đạn
        shootTimer += dt;
        if (shootTimer >= shootDelay) {
            shootTimer = 0.f;

            sf::FloatRect bounds = sprite.getGlobalBounds();

            // --- Tạo hai viên đạn song song ---
            float bulletY = bounds.top + bounds.height - 5.f; // vị trí xuất phát theo chiều dọc
            float offsetX = 20.f; // khoảng cách giữa 2 nòng

            // Trái và phải so với giữa thân
            sf::Vector2f leftPos(bounds.left + bounds.width / 2.f - offsetX, bulletY);
            sf::Vector2f rightPos(bounds.left + bounds.width / 2.f + offsetX, bulletY);

            bullets.emplace_back(leftPos);
            bullets.emplace_back(rightPos);
        }
    }


    // Cập nhật đạn
    for (auto& b : bullets)
        b.update(dt);

    // Xóa đạn ra khỏi màn hình
    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
            [](const Minion2Bullet& b) { return b.isOffScreen(1080.f); }),
        bullets.end());
}

void Minion2::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
    for (auto& b : bullets)
        b.draw(window);
}

bool Minion2::takeDamage(int dmg) {
    hp -= dmg;
    return hp <= 0;
}

sf::FloatRect Minion2::getBounds() const {
    return sprite.getGlobalBounds();
}

bool Minion2::isMarkedForDelete() const {
    return markedForDelete;
}

void Minion2::markForDelete() {
    markedForDelete = true;
}

bool Minion2::isOffScreen(float windowHeight) const
{
    return sprite.getPosition().y > windowHeight;
}
