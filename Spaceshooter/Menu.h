#pragma once
#include <SFML/Graphics.hpp>

class Menu {
public:
    enum MenuResult { NONE, PLAY, HIGHSCORE, QUIT };

    Menu(sf::RenderWindow& window);
    MenuResult show(sf::RenderWindow& window);

private:
    sf::Sprite background;
    sf::Sprite playButton;
    sf::Sprite highScoreButton;
    sf::Sprite quitButton;

    sf::Texture backgroundTex;
    sf::Texture playTex;
    sf::Texture highScoreTex;
    sf::Texture quitTex;
};
