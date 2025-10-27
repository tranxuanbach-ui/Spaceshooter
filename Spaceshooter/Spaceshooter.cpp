#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "player.h"
#include "MinionSpawner.h"
#include "Menu.h"
#include <fstream>

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 960), "Space Shooter");
    window.setFramerateLimit(60);

    // --- Hiển thị MENU ---
    Menu menu(window);
    Menu::MenuResult result = menu.show(window);

    if (result == Menu::QUIT)
        return 0;

    int lastScore = 0; // Lưu điểm của lần chơi vừa rồi
    int highScore = 0; //lưu điểm cao nhất đạt được

    // Đọc điểm cao nhất từ file
    std::ifstream highScoreFile("highscore.txt");
    if (highScoreFile.is_open()) {
        highScoreFile >> highScore;
        highScoreFile.close();
    }

    while (window.isOpen()) {
        if (result == Menu::PLAY) {
            bool isGameOver = false;

            sf::Font font;
            font.loadFromFile("Sprites/Fonts/arial/ARIAL.ttf");

            sf::Text gameOverText("GAME OVER", font, 60);
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setStyle(sf::Text::Bold);
            gameOverText.setPosition(100, 400);

            sf::Text finalScoreText("", font, 30);
            finalScoreText.setFillColor(sf::Color::White);
            finalScoreText.setPosition(120, 470);

            sf::Music backgroundMusic;
            if (backgroundMusic.openFromFile("Sprites/Music.ogg")) {
                backgroundMusic.setLoop(true);
                backgroundMusic.play();
            }

            sf::Texture backgroundTexture;
            backgroundTexture.loadFromFile("Sprites/Background.jpg");
            sf::Sprite backgroundSprite(backgroundTexture);
            backgroundSprite.setScale(
                (float)window.getSize().x / backgroundTexture.getSize().x,
                (float)window.getSize().y / backgroundTexture.getSize().y
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
                if (!isGameOver) {
                    player.update(deltaTime);
                    spawner.update(deltaTime, window.getSize().y);

                    // Va chạm
                    for (auto& m : spawner.getMinions1())
                        if (m.getBounds().intersects(player.getBounds())) { player.takeDamage(1); m.markForDelete(); }
                    for (auto& m : spawner.getMinions2())
                        if (m.getBounds().intersects(player.getBounds())) { player.takeDamage(1); m.markForDelete(); }
                    for (auto& m : spawner.getMinions3())
                        if (m.getBounds().intersects(player.getBounds())) { player.takeDamage(1); m.markForDelete(); }

                    spawner.cleanUpDeadMinions();

                    // Đạn va chạm
                    for (auto& bullet : player.getBullets()) {
                        for (auto& m : spawner.getMinions1())
                            if (bullet.getBounds().intersects(m.getBounds())) { if (m.takeDamage(1)) { m.markForDelete(); player.addScore(10); } bullet.markForDelete(); }
                        for (auto& m : spawner.getMinions2())
                            if (bullet.getBounds().intersects(m.getBounds())) { if (m.takeDamage(1)) { m.markForDelete(); player.addScore(10); } bullet.markForDelete(); }
                        for (auto& m : spawner.getMinions3())
                            if (bullet.getBounds().intersects(m.getBounds())) { if (m.takeDamage(1)) { m.markForDelete(); player.addScore(10); } bullet.markForDelete(); }
                    }

                    player.getBullets().erase(
                        std::remove_if(player.getBullets().begin(), player.getBullets().end(),
                            [](const Bullet& b) { return b.isMarkedForDelete(); }),
                        player.getBullets().end()
                    );

                    if (!player.isAlive()) {
                        isGameOver = true;
                        lastScore = player.getScore();

                        if (lastScore > highScore) {
                            highScore = lastScore;
                            std::ofstream outFile("highscore.txt");
                            if (outFile.is_open()) {
                                outFile << highScore;
                                outFile.close();
                            }
                        }
                    }
                }

                window.clear();
                window.draw(backgroundSprite);

                if (!isGameOver) {
                    player.draw(window);
                    spawner.draw(window);
                }
                else {
                    finalScoreText.setString("Final Score: " + std::to_string(player.getScore()));
                    window.draw(gameOverText);
                    window.draw(finalScoreText);
                }

                window.display();

                // Khi người chơi chết, quay lại menu sau 3s
                if (isGameOver) {
                    sf::sleep(sf::seconds(3));
                    result = menu.show(window);
                    if (result == Menu::QUIT) window.close();
                    break;
                }
            }
        }
        else if (result == Menu::HIGHSCORE) {
            // Hiển thị điểm số cao nhất
            sf::Font font;
            font.loadFromFile("Sprites/Fonts/arial/ARIAL.ttf");
            sf::Text scoreText("High Score: " + std::to_string(highScore), font, 40);
            scoreText.setFillColor(sf::Color::White);
            scoreText.setPosition(100, 430);

            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window.close();
                    if (event.type == sf::Event::MouseButtonPressed)
                        result = menu.show(window);
                }

                window.clear();
                window.draw(scoreText);
                window.display();

                if (result == Menu::PLAY || result == Menu::QUIT)
                    break;
            }
        }
    }
}
