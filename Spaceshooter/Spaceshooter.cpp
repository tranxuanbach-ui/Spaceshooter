#include <SFML/Graphics.hpp>
#include "player.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 960), "Space Shooter");
    window.setFramerateLimit(60);

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

        window.clear(sf::Color::Green);
        player.draw(window);
        window.display();
    }
}
