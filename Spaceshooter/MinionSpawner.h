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

public:
    MinionSpawner(float windowWidth);

    void update(float dt, float windowHeight);
    void draw(sf::RenderWindow& window);

    std::vector<Minion1>& getMinions1() { return minions1; }
    std::vector<Minion2>& getMinions2() { return minions2; }
    std::vector<Minion3>& getMinions3() { return minions3; }

    void cleanUpDeadMinions() {
        minions1.erase(std::remove_if(minions1.begin(), minions1.end(),
            [](const Minion1& m) { return m.isMarkedForDelete(); }), minions1.end());
        minions2.erase(std::remove_if(minions2.begin(), minions2.end(),
            [](const Minion2& m) { return m.isMarkedForDelete(); }), minions2.end());
        minions3.erase(std::remove_if(minions3.begin(), minions3.end(),
            [](const Minion3& m) { return m.isMarkedForDelete(); }), minions3.end());
    }

};
