#include "player.h"
#include <iostream>
#include <algorithm>

Player::Player(const sf::Vector2u& windowSize) {
    if (!texture.loadFromFile("Sprites/Player/plane.png"))
        std::cerr << "Error: Cannot load plane.png\n";

    if (!bulletTexture.loadFromFile("Sprites/Player/playerbullet.png"))
        std::cerr << "Error: Cannot load playerbullet.png\n";

    sprite.setTexture(texture);

    frameDelay = 0.08f;
    frameTimer = 0.f;
    currentFrame = 4;
    velocity = { 0.f, 0.f };

    movingLeft = movingRight = returningLeft = returningRight = false;

    for (int i = 0; i < 12; ++i)
        frames.push_back(sf::IntRect(i * 80, 0, 80, 120));

    sprite.setTextureRect(frames[currentFrame]);

    // --- Đặt máy bay ở giữa và gần cạnh dưới cửa sổ ---
    float windowWidth = static_cast<float>(windowSize.x);
    float windowHeight = static_cast<float>(windowSize.y);
    float spriteWidth = 80.f;
    float spriteHeight = 120.f;

    startPosition.x = (windowWidth - spriteWidth) / 2.f;
    startPosition.y = windowHeight - spriteHeight - 50.f;
    sprite.setPosition(startPosition);

    this->windowSize = windowSize;

    // --- Bullet ---
    shootDelay = 0.1f;  // bắn 10 viên/giây
    shootTimer = 0.f;
}

void Player::handleInput() {
    velocity = { 0.f, 0.f };
    bool aPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    bool dPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        velocity.y = -200.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        velocity.y = 200.f;
    if (aPressed)
        velocity.x = -200.f;
    if (dPressed)
        velocity.x = 200.f;

    if (aPressed) {
        movingLeft = true;
        movingRight = false;
        returningRight = false;
    }
    else if (dPressed) {
        movingRight = true;
        movingLeft = false;
        returningLeft = false;
    }
    else {
        if (movingLeft) {
            movingLeft = false;
            returningLeft = true;
        }
        if (movingRight) {
            movingRight = false;
            returningRight = true;
        }
    }
}

void Player::update(float deltaTime) {
    handleInput();

    // --- Cập nhật vị trí ---
    sprite.move(velocity * deltaTime);

    // --- Giới hạn trong màn hình ---
    sf::FloatRect bounds = sprite.getGlobalBounds();

    if (bounds.left < 0.f)
        sprite.setPosition(0.f, sprite.getPosition().y);
    if (bounds.left + bounds.width > windowSize.x)
        sprite.setPosition(windowSize.x - bounds.width, sprite.getPosition().y);
    if (bounds.top < 0.f)
        sprite.setPosition(sprite.getPosition().x, 0.f);
    if (bounds.top + bounds.height > windowSize.y)
        sprite.setPosition(sprite.getPosition().x, windowSize.y - bounds.height);

    frameTimer += deltaTime;
    shootTimer += deltaTime;

    // --- Animation ---
    if (movingLeft) {
        if (frameTimer >= frameDelay) {
            if (currentFrame > 1) currentFrame--;
            sprite.setTextureRect(frames[currentFrame]);
            frameTimer = 0.f;
        }
    }
    else if (returningLeft) {
        if (frameTimer >= frameDelay) {
            if (currentFrame < 3) currentFrame++;
            else if (currentFrame == 3) currentFrame = 0;
            sprite.setTextureRect(frames[currentFrame]);
            frameTimer = 0.f;
            if (currentFrame == 0) returningLeft = false;
        }
    }
    else if (movingRight) {
        if (frameTimer >= frameDelay) {
            if (currentFrame < 10) currentFrame++;
            sprite.setTextureRect(frames[currentFrame]);
            frameTimer = 0.f;
        }
    }
    else if (returningRight) {
        if (frameTimer >= frameDelay) {
            if (currentFrame < 11) currentFrame++;
            sprite.setTextureRect(frames[currentFrame]);
            frameTimer = 0.f;
            if (currentFrame == 11) returningRight = false;
        }
    }
    else {
        if (frameTimer >= frameDelay) {
            currentFrame++;
            if (currentFrame > 7 || currentFrame < 4)
                currentFrame = 4;
            sprite.setTextureRect(frames[currentFrame]);
            frameTimer = 0.f;
        }
    }

    // --- Auto shooting (2 dải song song gần thân máy bay) ---
    if (shootTimer >= shootDelay) {
        sf::Vector2f pos = sprite.getPosition();
        sf::FloatRect bounds = sprite.getGlobalBounds();

        float centerX = pos.x + bounds.width / 2.f;
        float topY = pos.y;
        float offsetX = 22.f;
        float bulletY = topY + 15.f;

        bullets.emplace_back(&bulletTexture, sf::Vector2f(centerX - offsetX, bulletY));
        bullets.emplace_back(&bulletTexture, sf::Vector2f(centerX + offsetX, bulletY));

        shootTimer = 0.f;
    }

    // --- Update bullets ---
    for (auto& b : bullets)
        b.update(deltaTime);

    // --- Xoá đạn ra khỏi màn hình ---
    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
            [](Bullet& b) { return b.isOffScreen(); }),
        bullets.end());
}

void Player::draw(sf::RenderWindow& window) {
    for (auto& b : bullets)
        b.draw(window);
    window.draw(sprite);
}
