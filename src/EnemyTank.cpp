#include "include/EnemyTank.hpp"

EnemyTank::EnemyTank(sf::Vector2f initial_pos, float speed_scaler) 
  : Tank(initial_pos, speed_scaler) {
      textureNoTurret_.loadFromFile("../src/assets/RedTankNoTurret.png");
      tank_shape_.setTexture(&textureNoTurret_);
      textureTurret_.loadFromFile("../src/assets/RedTankTurret.png");
      turret_shape_.setTexture(&textureTurret_);
  }

void EnemyTank::Update(std::vector<Projectile> &projectiles, const sf::RectangleShape &player_tank, const std::vector<Wall> &walls, const std::vector<Spike> &spikes) {
  float angle = GetAngleToPlayer(player_tank);
  UpdateShape(angle, walls, spikes);
  if (cooldown_timer_ > 150) {
    cooldown_timer_ = 0;
    Shoot(projectiles, angle);
  }
  ++cooldown_timer_;
 
}
/**
 * @brief Gives the rotation angle as radians, rotates the tank using degrees.
 * 
 * @param rotation_angle 
 * 
 * NOTE: "walls" ans "spikes" commented out temporarily as they are currently not used in this implementation.
 */
void EnemyTank::UpdateShape(float rotation_angle, const std::vector<Wall> &walls, const std::vector<Spike> &spikes) {
  turret_shape_.setRotation(rotation_angle * 180 / M_PI + 180);
  if (!goForward(walls, spikes, 2)) {
    turnLeft(walls, spikes, 1);  
  }
}


float EnemyTank::GetAngleToPlayer(sf::RectangleShape player_tank) { 
  sf::Vector2f player_position = player_tank.getPosition();

  float dx = turret_shape_.getPosition().x - player_position.x;
  float dy = turret_shape_.getPosition().y - player_position.y;

  return atan2(dy, dx);
}


