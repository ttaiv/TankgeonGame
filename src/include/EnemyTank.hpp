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
    // Copy constructor and copy assignment are deleted to avoid losing textures.
    EnemyTank(const EnemyTank &other) = delete;
    EnemyTank& operator=(const EnemyTank &other) = delete;
    
    void Update(std::vector<Projectile> &projectiles, const sf::RectangleShape &playerTank, const std::vector<Wall> &walls, const std::vector<Spike> &spikes);
    

  private:
    void UpdateShape(float rotation_angle, const std::vector<Wall> &walls, const std::vector<Spike> &spikes);
    float GetAngleToPlayer(sf::RectangleShape playerTank);
    sf::Texture textureNoTurret_;
    sf::Texture textureTurret_;
    bool IsTooClose(std::vector<Wall> &walls, std::vector<Spike> &spikes);

};