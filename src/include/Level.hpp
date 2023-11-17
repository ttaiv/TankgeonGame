#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include "CollisionManager.hpp"
#include "LevelData.hpp"


class Level {
  public:
    Level(sf::RenderWindow &window);
    // Disallow copying
    Level(const Level &other) = delete;
    Level& operator=(const Level &other) = delete;

    void UpdateLevel(sf::RenderWindow &window);
    void DrawLevel(sf::RenderWindow &window);
    bool IsCompleted() const;
    LevelData GetLevelData();
    

    

  private:
    void HandleProjectileCollisions();
    LevelData level_data_;
};