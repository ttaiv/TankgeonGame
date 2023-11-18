#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include "Tank.hpp"
#include "PlayerTank.hpp"

class EnemyTank: public Tank {
  public:
    EnemyTank(sf::Vector2f initial_pos, float speed_scaler, PlayerTank &player);
    EnemyTank(const EnemyTank &other); //Custom copy constructor to keep textures
    EnemyTank& operator=(const EnemyTank &other) = delete;
    
    void Update(LevelData &level_data_);
    
    bool WillBeHit(LevelData &level_data_) const;
    bool CanSeePlayer(LevelData &level_data_) const;

  private:
    void UpdateShape(float rotation_angle, LevelData &level_data_);
    float GetAngleToPlayer();
    sf::Texture textureNoTurret_;
    sf::Texture textureTurret_;
    bool IsTooClose();
    const PlayerTank &player_;

};