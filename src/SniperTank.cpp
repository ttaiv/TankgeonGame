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

SniperTank::MovementOption SniperTank::ChooseMovement() {
  movement_timer_ = 0;
  return static_cast<MovementOption>(movement_dis_(gen_));
}


void SniperTank::UpdateShape(float rotation_angle, LevelData &level_data_) {
  turret_shape_.setRotation(rotation_angle * 180 / M_PI + 180);

  // One movement has lasted long enough, choose a new movement.
  if (movement_timer_ > SINGLE_MOVEMENT_DURATION) {
    current_movement_ = ChooseMovement();
  }
  
  if (current_movement_ == MovementOption::TurnLeft) {
    if (!Tank::TurnLeft(1, level_data_)) {
      // If we can't turn left, choose a new movement.
      current_movement_ = ChooseMovement();
    }
  }
  if (current_movement_ == MovementOption::TurnRight) {
    if (!Tank::TurnRight(1, level_data_)) {
      // If we can't turn right, choose a new movement.
      current_movement_ = ChooseMovement();
    }
  }
  if (current_movement_ == MovementOption::GoBack) {
    if (!Tank::GoBack(1, level_data_)) {
      // If we can't go back, choose a new movement.
      current_movement_ = ChooseMovement();
    }
  }
  if (current_movement_ == MovementOption::GoForward1 || current_movement_ == MovementOption::GoForward2) {
    if (!Tank::GoForward(1, level_data_)) {
      // If we can't go forward, choose a new movement.
      current_movement_ = ChooseMovement();
    }
  }
  ++movement_timer_;
}