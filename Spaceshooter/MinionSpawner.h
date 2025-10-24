#pragma once
#include <SFML/Graphics.hpp>
#include "Minion1.h"
#include "Minion2.h"
#include "Minion3.h"
#include <vector>

class MinionSpawner
{
private:
    std::vector<Minion1> minions1;
    std::vector<Minion2> minions2;
    std::vector<Minion3> minions3;

    float timer1, delay1; // Minion1
    float timer2, delay2; // Minion2
	float timer3, delay3; // Minion3
    float windowWidth;

    // Hàm kiểm tra vị trí có an toàn để spawn không
    bool isPositionSafe(const sf::FloatRect& newBounds) const;

public:
    MinionSpawner(float windowWidth);

    void update(float dt, float windowHeight);
    void draw(sf::RenderWindow& window);
};
