#include "include/SniperTank.hpp"

SniperTank::SniperTank(sf::Vector2f initial_pos, PlayerTank &player)
  : EnemyTank(initial_pos, SNIPER_TANK_SPEED, player) {
    chassis_texture_.loadFromFile("../src/assets/tanks/RedTankNoTurret.png");
    tank_shape_.setTexture(&chassis_texture_);
    turret_texture_.loadFromFile("../src/assets/tanks/RedTankTurret.png");
    turret_shape_.setTexture(&turret_texture_);
    points_ = 150;
  }


void SniperTank::Update(LevelData &level_data_) {
  float angle = GetAngleToPlayer();
  UpdateShape(angle, level_data_);
  bool can_shoot = CanShoot(); // call every frame to update cooldown timer
  if (can_shoot && CanSeePlayer(level_data_)) {
    Shoot(angle, level_data_, 0, SNIPER_PROJECTILE_SPEED); // ricochet limit is zero for sniper
  }
  ++fire_cooldown_timer_;
}

void SniperTank::UpdateShape(float rotation_angle, LevelData &level_data_) {
  turret_shape_.setRotation(rotation_angle * 180 / M_PI + 180);
  
  if (movement_timer_ > SINGLE_MOVEMENT_DURATION) {
    current_movement_ = static_cast<MovementOption>(movement_dis_(gen_));
    movement_timer_ = 0;
  }
  
  if (current_movement_ == MovementOption::TurnLeft){
    Tank::TurnLeft(1, level_data_);
  }
  else if (current_movement_ == MovementOption::TurnRight){
    Tank::TurnRight(1, level_data_);
  }
  else if (current_movement_ == MovementOption::GoBack){
    Tank::GoBack(2, level_data_);
  }
  else {
    Tank::GoForward(2, level_data_);
  }
  ++movement_timer_;
}