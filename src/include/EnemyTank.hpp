#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include "Tank.hpp"

class EnemyTank: public Tank {
  public:
    EnemyTank(sf::Vector2f initial_pos, float speed_scaler, LevelData &level_data);
    // Copy constructor and copy assignment are deleted to avoid losing textures.
    EnemyTank(const EnemyTank &other) = delete;
    EnemyTank& operator=(const EnemyTank &other) = delete;
    
    void Update();
    
    bool WillBeHit() const;
    bool CanSeePlayer() const;

  private:
    void UpdateShape(float rotation_angle);
    float GetAngleToPlayer();
    sf::Texture textureNoTurret_;
    sf::Texture textureTurret_;
    bool IsTooClose();

};