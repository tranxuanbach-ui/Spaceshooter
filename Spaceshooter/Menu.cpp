#include "Menu.h"

Menu::Menu(sf::RenderWindow& window) {
    // Load textures
    backgroundTex.loadFromFile("Sprites/Menu/MenuBackground.png");
    playTex.loadFromFile("Sprites/Menu/Play.png");
    highScoreTex.loadFromFile("Sprites/Menu/High Score.png");
    quitTex.loadFromFile("Sprites/Menu/Quit.png");

    // Set sprites
    background.setTexture(backgroundTex);
    playButton.setTexture(playTex);
    highScoreButton.setTexture(highScoreTex);
    quitButton.setTexture(quitTex);

    // Scale background để vừa window
    background.setScale(
        (float)window.getSize().x / backgroundTex.getSize().x,
        (float)window.getSize().y / backgroundTex.getSize().y
    );

    //Giảm kích thước của nút xuống 60%
    float buttonScale = 0.6f;
    playButton.setScale(buttonScale, buttonScale);
    highScoreButton.setScale(buttonScale, buttonScale);
    quitButton.setScale(buttonScale, buttonScale);

    // Center buttons horizontally and place vertically in lower half
    float centerX = window.getSize().x / 2.0f;
    float startY = window.getSize().y * 0.6f; // bắt đầu từ giữa dưới
    float spacing = 110.0f; //Khoảng cách giữa các nút

    playButton.setPosition(centerX - playButton.getGlobalBounds().width / 2, startY);
    highScoreButton.setPosition(centerX - highScoreButton.getGlobalBounds().width / 2, startY + 90);
    quitButton.setPosition(centerX - quitButton.getGlobalBounds().width / 2, startY + 180);
}

Menu::MenuResult Menu::show(sf::RenderWindow& window) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                return QUIT;

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos((float)event.mouseButton.x, (float)event.mouseButton.y);

                if (playButton.getGlobalBounds().contains(mousePos))
                    return PLAY;
                if (highScoreButton.getGlobalBounds().contains(mousePos))
                    return HIGHSCORE;
                if (quitButton.getGlobalBounds().contains(mousePos))
                    window.close();     //thoát game
                    return QUIT;
            }
        }

        // Draw everything
        window.clear();
        window.draw(background);
        window.draw(playButton);
        window.draw(highScoreButton);
        window.draw(quitButton);
        window.display();
    }

    return QUIT;
}
