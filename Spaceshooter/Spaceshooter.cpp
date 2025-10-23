#include<SFML/Graphics.hpp>
#include "player.h"
#include<SFML/Audio.hpp>
#include"MinionSpawner.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(500, 960), "Space Shooter");              //tạo 1 cửa sổ window
    window.setFramerateLimit(60);                                                   //giới hạn tốc độ khung hình

	sf::Music backgroundMusic;
	if (!backgroundMusic.openFromFile("Sprites/Music.ogg")) {                       //tải nhạc nền
        return -1;
	}

	backgroundMusic.setLoop(true);                                                  //lặp lại nhạc nền
	backgroundMusic.play();                                                         //phát nhạc nền

	sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Sprites/Background.jpg")) {
        return -1;
    }

	sf::Sprite backgroundSprite;                                                    // Tạo sprite để hiển thị background
	backgroundSprite.setTexture(backgroundTexture);

    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,     //scale để chiều ngang background vừa với chiều ngang cửa sổ window
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y      //scale chiều dọc y hệt dòng trên
	);

	MinionSpawner spawner(window.getSize().x);

    Player player(window.getSize());
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();
        player.update(deltaTime);
		spawner.update(deltaTime, window.getSize().y);

        window.clear();
		window.draw(backgroundSprite);
        player.draw(window);
        spawner.draw(window);
        window.display();
    }
}
