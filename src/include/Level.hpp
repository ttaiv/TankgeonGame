#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <list>
#include "Projectile.hpp"
#include "Tank.hpp"
#include "Wall.hpp"
#include "Spike.hpp"
#include "PlayerTank.hpp"
#include "EnemyTank.hpp"
#include "CollisionManager.hpp"

class Level {
  public:
    Level(PlayerTank player, sf::RenderWindow &window);
    // Disallow copying
    Level(const Level &other) = delete;
    Level& operator=(const Level &other) = delete;

    void UpdateLevel(sf::RenderWindow &window);
    void DrawLevel(sf::RenderWindow &window);
    bool IsCompleted() const;

  private:
    std::vector<Wall> walls_;
    std::vector<Spike> spikes_;
    std::list<EnemyTank> enemies_;
    PlayerTank player_;
    std::vector<Projectile> projectiles_;

    void HandleProjectileCollisions();

};