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
    // Copy constructor and copy assignment are needed to correctly load the texture
    EnemyTank(const EnemyTank &other);
    EnemyTank& operator=(const EnemyTank &other);
    
    void Update(std::vector<Projectile> &projectiles, const sf::RectangleShape &playerTank, const std::vector<Wall> &walls, const std::vector<Spike> &spikes);
    

  private:
    void UpdateShape(float rotation_angle, const std::vector<Wall> &walls, const std::vector<Spike> &spikes);
    float GetAngleToPlayer(sf::RectangleShape playerTank);
    sf::Texture textureNoTurret_;
    sf::Texture textureTurret_;
    bool IsTooClose(std::vector<Wall> &walls, std::vector<Spike> &spikes);
};