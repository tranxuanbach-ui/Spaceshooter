#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Minion2Bullet
{
private:
    sf::Sprite sprite;
    static sf::Texture huhtexture;
    float speed;
	bool markedForDelete = false;

public:
    Minion2Bullet(const sf::Vector2f& pos)
    {
        huhtexture.loadFromFile("Sprites/Enemies/EnemyBullet1.png");
        sprite.setTexture(huhtexture);
        sprite.setPosition(pos);
        sprite.setRotation(90.f);
		sprite.setScale(1.f, 1.f);  // điều chỉnh kích thước đạn nếu cần
		speed = 500.f;              // tốc độ di chuyển của đạn
    }

    void update(float dt) { sprite.move(0.f, speed * dt); }
    void draw(sf::RenderWindow& window) { window.draw(sprite); }
    bool isOffScreen(float windowHeight) const { return sprite.getPosition().y > windowHeight; }

    //Phần va chạm
	sf::FloatRect getBounds() const { return sprite.getGlobalBounds(); }
	void markForDelete() { markedForDelete = true; }
	bool isMarkedForDelete() const { return markedForDelete; }
};

class Minion2
{
private:
    sf::Sprite sprite;
    static sf::Texture texture;
    float speed;
    bool stopped;
    float stopY;
	int hp;         // điểm máu của Minion2
	bool markedForDelete = false; // đánh dấu để xóa Minion2 khi bị tiêu diệt

    float shootTimer;
    float shootDelay;

public:
    std::vector<Minion2Bullet> bullets;

    Minion2(const sf::Vector2f& startPos);
    void update(float dt);
    void draw(sf::RenderWindow& window);
    bool isOffScreen(float windowHeight) const;

	sf::Vector2f getPosition() const { return sprite.getPosition(); }       // Lấy vị trí của Minion2

    bool takeDamage(int dmg);
    sf::FloatRect getBounds() const;

    bool isMarkedForDelete() const;
    void markForDelete();

	std::vector<Minion2Bullet>& getBullets() { return bullets; }//truy cập danh sách đạn
};


