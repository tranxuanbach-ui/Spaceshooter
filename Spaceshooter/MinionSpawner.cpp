#include "MinionSpawner.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

MinionSpawner::MinionSpawner(float windowWidth)
{
    this->windowWidth = windowWidth;

    // --- Timer khởi tạo ---
    timer1 = 0.f;
    timer2 = 0.f;
	timer3 = 0.f;

    // --- Độ trễ spawn riêng ---
    delay1 = 1.0f;  // Minion1 spawn mỗi 1 giây
    delay2 = 3.f;  // Minion2 spawn mỗi 3 giây
	delay3 = 5.f;  // Minion3 spawn mỗi 5 giây

    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void MinionSpawner::update(float dt, float windowHeight)
{
    timer1 += dt;
    timer2 += dt;
    timer3 += dt;

    // --- Spawn Minion1 ---
    if (timer1 >= delay1) {
        float x = static_cast<float>(std::rand() % static_cast<int>(windowWidth - 100) + 50);
        minions1.emplace_back(sf::Vector2f(x, -50.f));
        timer1 = 0.f;
    }

    // --- Spawn Minion2 ---
    if (timer2 >= delay2) {
        float x = static_cast<float>(std::rand() % static_cast<int>(windowWidth - 100) + 50);
        minions2.emplace_back(sf::Vector2f(x, -50.f));
        timer2 = 0.f;
    }

    // --- Spawn Minion3 (đội hình 3x3) ---
    if (timer3 >= delay3)
    {
        timer3 = 0.f;

        bool leftToRight = (std::rand() % 2 == 0); // 50% hướng trái -> phải, 50% ngược lại
        sf::Vector2f dir = leftToRight ? sf::Vector2f(1.f, 1.f) : sf::Vector2f(-1.f, 1.f);
        float startX = leftToRight ? -100.f : windowWidth + 100.f;

        float baseY = 100.f;        // vị trí xuất phát cao nhất
        float spacing = 70.f;       // khoảng cách giữa các minion

        // 2 hàng × 3 cột
        for (int row = 0; row < 2; ++row)
        {
            for (int col = 0; col < 3; ++col)
            {
                float xOffset = leftToRight ? (col * spacing) : -(col * spacing);
                float yOffset = row * spacing;
                minions3.emplace_back(sf::Vector2f(startX + xOffset, baseY - yOffset), dir);
            }
        }
    }

    // --- Update ---
    for (auto& m : minions1) m.update(dt);
    for (auto& m : minions2) m.update(dt);
    for (auto& m : minions3) m.update(dt);

    // --- Xóa quái ---
    minions3.erase(std::remove_if(minions3.begin(), minions3.end(),
        [&](const Minion3& m) { return m.isOffScreen(windowWidth, windowHeight); }),
        minions3.end());
}

void MinionSpawner::draw(sf::RenderWindow& window)
{
    for (auto& m : minions1) m.draw(window);
    for (auto& m : minions2) m.draw(window);
    for (auto& m : minions3) m.draw(window);
}

