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
    void Update(std::vector<Projectile> &projectiles, sf::RectangleShape playerTank, std::vector<Wall> &walls, std::vector<Spike> &spikes);
    

  private:
    void UpdateShape(float rotation_angle, std::vector<Wall> &walls, std::vector<Spike> &spikes);
    float GetAngleToPlayer(sf::RectangleShape playerTank);
};