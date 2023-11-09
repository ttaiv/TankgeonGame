#include "include/EnemyTank.hpp"

EnemyTank::EnemyTank(sf::Vector2f initial_pos, float speed_scaler) 
  : Tank(initial_pos, speed_scaler) {}

void EnemyTank::Update(std::vector<Projectile> &projectiles, sf::RectangleShape player_tank) {
  float angle = GetAngleToPlayer(player_tank);
  UpdateShape(angle);
  if (cooldown_timer_ > 30) {
    cooldown_timer_ = 0;
    Shoot(projectiles, angle);
  }
  ++cooldown_timer_;
}
/**
 * @brief Gives the rotation angle as radians, rotates the tank using degrees.
 * 
 * @param rotation_angle 
 */
void EnemyTank::UpdateShape(float rotation_angle) {
  turret_shape_.setRotation(rotation_angle * 180 / M_PI + 180);
}
float EnemyTank::GetAngleToPlayer(sf::RectangleShape player_tank) { 
  sf::Vector2f player_position = player_tank.getPosition();

  float dx = turret_shape_.getPosition().x - player_position.x;
  float dy = turret_shape_.getPosition().y - player_position.y;

  return atan2(dy, dx);
}


