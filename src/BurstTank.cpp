#include "include/BurstTank.hpp"

BurstTank::BurstTank(sf::Vector2f initial_pos, PlayerTank &player)
  : EnemyTank(initial_pos, BURST_TANK_SPEED, player, PLAYER_FIRE_COOLDOWN) { // same cooldown as player
    chassis_texture_.loadFromFile("../src/assets/tanks/BlueTankNoTurret.png");
    tank_shape_.setTexture(&chassis_texture_);
    turret_texture_.loadFromFile("../src/assets/tanks/BlueTankTurret.png");
    turret_shape_.setTexture(&turret_texture_);
    points_ = 250;
  }

float BurstTank::GetRandomAngle() {
  float angle = angle_dis_(gen_);
  if (angle_sign_dis_(gen_) == 1) {
    angle *= -1;
  }
  return angle;
}

void BurstTank::Update(LevelData &level_data_) {
  float shooting_angle = GetAngleToPlayer() + GetRandomAngle();
  UpdateShape(GetAngleToPlayer(), level_data_);
  bool can_shoot = CanShoot(); // call to update cooldown timers
  if (can_shoot && CanSeePlayer(level_data_)) { 
    turret_shape_.setRotation(shooting_angle * 180 / M_PI + 180);
    Shoot(shooting_angle, level_data_, 1, BASE_PROJECTILE_SPEED);
  }
}


void BurstTank::UpdateShape(float rotation_angle, LevelData &level_data_) {
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