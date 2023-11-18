#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include "CollisionManager.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "Wall.hpp"
#include "Spike.hpp"
#include "PlayerTank.hpp"
#include "EnemyTank.hpp"
#include "Projectile.hpp"

struct LevelData {
  std::vector<Wall> walls_;
  std::vector<Spike> spikes_;
  std::list<EnemyTank> enemies_;
  std::vector<Projectile> projectiles_;
};

class Level {
  public:
    Level(sf::RenderWindow &window, LevelData level_data);
    // Disallow copying
    Level(const Level &other) = delete;
    Level& operator=(const Level &other) = delete;

    void UpdateLevel(sf::RenderWindow &window);
    void DrawLevel(sf::RenderWindow &window);
    bool IsCompleted() const;
    const LevelData& GetLevelData();
    
  private:
    void HandleProjectileCollisions();
    LevelData level_data_;
    PlayerTank player_; 
};