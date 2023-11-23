#include "include/BurstTank.hpp"

BurstTank::BurstTank(sf::Vector2f initial_pos, PlayerTank &player)
  : EnemyTank(initial_pos, BURST_TANK_SPEED, player) {
    chassis_texture_.loadFromFile("../src/assets/tanks/BlueTankNoTurret.png");
    tank_shape_.setTexture(&chassis_texture_);
    turret_texture_.loadFromFile("../src/assets/tanks/BlueTankTurret.png");
    turret_shape_.setTexture(&turret_texture_);
  }

float BurstTank::GetRandomAngle() {
  float angle = dis_(gen_);
  if (sign_dis(gen_) == 1) {
    angle *= -1;
  }
  return angle;
}

void BurstTank::Update(LevelData &level_data_) {
  float shooting_angle = GetAngleToPlayer() + GetRandomAngle();
  UpdateShape(GetAngleToPlayer(), level_data_);
  if (fire_cooldown_timer_ > PLAYER_FIRE_COOLDOWN && CanSeePlayer(level_data_)) { // same cooldown as player
    turret_shape_.setRotation(shooting_angle * 180 / M_PI + 180);
    fire_cooldown_timer_ = 0;
    Shoot(shooting_angle, level_data_, 1, BASE_PROJECTILE_SPEED);
  }
  ++fire_cooldown_timer_;
}


void BurstTank::UpdateShape(float rotation_angle, LevelData &level_data_) {
  turret_shape_.setRotation(rotation_angle * 180 / M_PI + 180);
  //Introduce randomness
  std::srand(std::time(nullptr));
  double randomFloat = static_cast<double>(std::rand()) / RAND_MAX;
  
  if (randomFloat < 0.25){
    TurnLeft(1, level_data_);
  }
  else if (randomFloat < 0.50){
    GoForward(2, level_data_);
  }
  else if (randomFloat < 0.75){
    GoBack(2, level_data_);
  }
  else{
    TurnRight(1, level_data_);
  }
}