#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include "Projectile.hpp"
#include "Tank.hpp"
#include "Wall.hpp"
#include "Spike.hpp"

class EnemyTank: public Tank {
  public:
    EnemyTank(sf::Vector2f initial_pos, float speed_scaler);
    void Update(std::vector<Projectile> &projectiles, sf::RectangleShape playerTank);
    bool IsCollided(sf::Vector2f next_pos, std::vector<Wall> &walls, std::vector<Spike> &spikes) const;

  private:
    void UpdateShape(float rotation_angle);
    float GetAngleToPlayer(sf::RectangleShape playerTank);
};