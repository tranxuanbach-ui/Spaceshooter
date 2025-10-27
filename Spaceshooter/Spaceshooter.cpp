#include <SFML/Graphics.hpp>
#include "player.h"
#include<SFML/Audio.hpp>
#include"MinionSpawner.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(500, 960), "Space Shooter");              //tạo 1 cửa sổ window
    window.setFramerateLimit(60);                                                   //giới hạn tốc độ khung hình

    bool isGameOver = false;
    sf::Font font;
    font.loadFromFile("Sprites/Fonts/arial/ARIAL.ttf");

    sf::Text gameOverText;
    sf::Text finalScoreText;

    // "GAME OVER"
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(60);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setPosition(100, 400);

    // Final Score
    finalScoreText.setFont(font);
    finalScoreText.setCharacterSize(30);
    finalScoreText.setFillColor(sf::Color::White);
    finalScoreText.setPosition(120, 470);

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

	MinionSpawner spawner(window.getSize().x);      //khởi tạo spawn quái 

    Player player(window.getSize());        //khởi tạo player

    sf::Clock clock;


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		float deltaTime = clock.restart().asSeconds();      //tạo biến deltaTime để đồng bộ hóa tốc độ khung hình
        if (!isGameOver) {
            player.update(deltaTime);                           //cập nhật trạng thái của player
            spawner.update(deltaTime, window.getSize().y);      //cập nhật trạng thái của spawner

            //Va chạm giữa Player và các Minion
            for (auto& m : spawner.getMinions1())
            {
                if (m.getBounds().intersects(player.getBounds()))
                {
                    player.takeDamage(1);
                    m.markForDelete();
                }
            }

            for (auto& m : spawner.getMinions2())
            {
                if (m.getBounds().intersects(player.getBounds()))
                {
                    player.takeDamage(1);
                    m.markForDelete();
                }
            }

            for (auto& m : spawner.getMinions3())
            {
                if (m.getBounds().intersects(player.getBounds()))
                {
                    player.takeDamage(1);
                    m.markForDelete();
                }
            }

            // Xóa quái đã bị đánh dấu
            spawner.cleanUpDeadMinions();

            // --- Kiểm tra va chạm giữa đạn player và các minion ---
            for (auto& bullet : player.getBullets())
            {
                // Minion1
                for (auto& m : spawner.getMinions1())
                {
                    if (bullet.getBounds().intersects(m.getBounds()))
                    {
                        if (m.takeDamage(1)) {
                            m.markForDelete();
                            player.addScore(10);        //Cộng 10 điểm
                        }
                        bullet.markForDelete();
                    }
                }

                // Minion2
                for (auto& m : spawner.getMinions2())
                {
                    if (bullet.getBounds().intersects(m.getBounds()))
                    {
                        if (m.takeDamage(1)) {
                            m.markForDelete();
                            player.addScore(10);        //Cộng 10 điểm
                        }
                        bullet.markForDelete();
                    }
                }

                // Minion3
                for (auto& m : spawner.getMinions3())
                {
                    if (bullet.getBounds().intersects(m.getBounds()))
                    {
                        if (m.takeDamage(1)) {
                            m.markForDelete();
                            player.addScore(10);
                        }
                        bullet.markForDelete();
                    }
                }
            }

            // Xóa đạn và quái đã bị đánh dấu
            player.getBullets().erase(
                std::remove_if(player.getBullets().begin(), player.getBullets().end(),
                    [](const Bullet& b) { return b.isMarkedForDelete(); }),
                player.getBullets().end()
            );

            if (!player.isAlive()) {
                isGameOver = true;
            }
        }

        spawner.cleanUpDeadMinions();


        window.clear();
        window.draw(backgroundSprite);

        if (!isGameOver) {
            player.draw(window);
            spawner.draw(window);
        }
        else {
            gameOverText.setString("GAME OVER");
            finalScoreText.setString("Final Score: " + std::to_string(player.getScore()));

            window.draw(gameOverText);
            window.draw(finalScoreText);
        }

        window.display();

    }
}
