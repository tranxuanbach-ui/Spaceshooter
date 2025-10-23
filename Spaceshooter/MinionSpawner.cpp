#include "MinionSpawner.h"

MinionSpawner::MinionSpawner(float windowWidth)
{
    this->windowWidth = windowWidth;
	spawnTimer = 0.f;   // Bộ đếm thời gian sinh minion
    spawnDelay = 1.f;   // Sinh 1 con sau mỗi 1.5 giây
	std::srand(static_cast<unsigned>(std::time(nullptr)));      // khởi tạo bộ sinh số ngẫu nhiên
}

void MinionSpawner::update(float dt, float windowHeight)
{
    spawnTimer += dt;

    // Khi đủ thời gian, sinh ra 1 con mới
    if (spawnTimer >= spawnDelay)
    {
        float x = static_cast<float>(std::rand() % static_cast<int>(windowWidth - 100) + 50);
        minions.emplace_back(sf::Vector2f(x, -50.f)); // xuất hiện trên đầu màn hình
        spawnTimer = 0.f;
    }

    // Cập nhật vị trí từng con
    for (auto& m : minions)
        m.update(dt);

    // Xóa những con bay ra khỏi màn hình
    minions.erase(
        std::remove_if(minions.begin(), minions.end(),
            [&](const Minion1& m) { return m.isOffScreen(windowHeight); }),
        minions.end()
    );
}

void MinionSpawner::draw(sf::RenderWindow& window)
{
    for (auto& m : minions)
        m.draw(window);
}
