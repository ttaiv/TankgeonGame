#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include "Projectile.hpp"
#include "Tank.hpp"
#include "Wall.hpp"
#include "Spike.hpp"
#include "PlayerTank.hpp"
#include "EnemyTank.hpp"
#include "CollisionManager.hpp"

class Level {
  public:
    Level(PlayerTank player);
    void SetUpLevel(int level_number, sf::RenderWindow &window);
    void UpdateLevel(sf::RenderWindow &window);
    void DrawLevel(sf::RenderWindow &window);

  private:
    std::vector<Wall> walls_;
    std::vector<Spike> spikes_;
    std::vector<EnemyTank> enemies_;
    PlayerTank player_;
    std::vector<Projectile> projectiles_;

    void HandleProjectileCollisions();

};