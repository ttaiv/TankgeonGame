#include "include/StationaryTank.hpp"

StationaryTank::StationaryTank(sf::Vector2f initial_pos, PlayerTank &player)
  : EnemyTank(initial_pos, 0, player) {
    points_ = 100;
    chassis_texture_.loadFromFile("../src/assets/tanks/BlueTankNoTurret.png");
    tank_shape_.setTexture(&chassis_texture_);
    turret_texture_.loadFromFile("../src/assets/tanks/BlueTankTurret.png");
    turret_shape_.setTexture(&turret_texture_);
  }

float StationaryTank::GetRandomAngle() {
  float angle = angle_dis_(gen_);
  if (angle_sign_dis_(gen_) == 1) {
    angle *= -1;
  }
  return angle;
}

void StationaryTank::Update(LevelData &level_data_) {
  float angle = GetAngleToPlayer() + GetRandomAngle();
  bool can_shoot = CanShoot(); // call every frame to update cooldown timer
  if (can_shoot && CanSeePlayer(level_data_)) {
    turret_shape_.setRotation(angle * 180 / M_PI + 180);
    Shoot(angle, level_data_, 1, BASE_PROJECTILE_SPEED);
  }
  ++fire_cooldown_timer_;
}