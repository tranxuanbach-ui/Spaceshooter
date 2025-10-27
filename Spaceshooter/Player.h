#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Bullet.h"

class Player {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Texture bulletTexture;
    float frameDelay, frameTimer;
    int currentFrame;
    sf::Vector2f velocity;
    bool movingLeft, movingRight, returningLeft, returningRight;
    std::vector<sf::IntRect> frames;

	float shootDelay, shootTimer;       // thời gian giữa các lần bắn đạn
	std::vector<Bullet> bullets;        // danh sách đạn của player

	sf::Vector2u windowSize;        // kích thước cửa sổ
	sf::Vector2f startPosition;     // vị trí bắt đầu của player

	int hp;         // điểm máu của player
	bool isDead;    // trạng thái sống/chết của player

    //Hiển thị HP player
    sf::Font font;
    sf::Text hpText;

    int score;
    sf::Font scoreFont;
    sf::Text scoreText;

public:
    Player(const sf::Vector2u& windowSize);
    void handleInput();
    void update(float deltaTime);           
    void draw(sf::RenderWindow& window);
	const std::vector<Bullet>& getBullets() const { return bullets; }   // chỉ cho phép đọc đạn
	std::vector<Bullet>& getBullets() { return bullets; }               // cho phép sửa đổi đạn

    sf::FloatRect getBounds() const { return sprite.getGlobalBounds(); }
    bool markedForDelete = false;
    void markForDelete() { markedForDelete = true; }
    bool isMarkedForDelete() const { return markedForDelete; }

    int getHP() const { return hp;}
	bool isAlive() const { return !isDead; }
	void takeDamage(int dmg);

    void updateHpText(); //Cập nhật và hiển thị HP

    int getScore() const { return score; }
    void addScore(int amount) { score += amount; updateScoreText(); }
    void updateScoreText();
};
