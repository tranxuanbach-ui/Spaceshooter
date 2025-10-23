#pragma once
#include <SFML/Graphics.hpp>
#include "Minion1.h"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

class MinionSpawner
{
private:
    std::vector<Minion1> minions;
    float spawnTimer;
    float spawnDelay;
    float windowWidth;

public:
    MinionSpawner(float windowWidth);

    void update(float dt, float windowHeight);
    void draw(sf::RenderWindow& window);
};
