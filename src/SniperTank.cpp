#include "include/SniperTank.hpp"

SniperTank::SniperTank(sf::Vector2f initial_pos, PlayerTank &player)
  : EnemyTank(initial_pos, SNIPER_TANK_SPEED, player) {
    chassis_texture_.loadFromFile("../src/assets/tanks/RedTankNoTurret.png");
    tank_shape_.setTexture(&chassis_texture_);
    turret_texture_.loadFromFile("../src/assets/tanks/RedTankTurret.png");
    turret_shape_.setTexture(&turret_texture_);
  }


void SniperTank::Update(LevelData &level_data_) {
  float angle = GetAngleToPlayer();
  UpdateShape(angle, level_data_);
  if (fire_cooldown_timer_ > 150 && CanSeePlayer(level_data_)) {
    fire_cooldown_timer_ = 0;
    Shoot(angle, level_data_, 0, SNIPER_PROJECTILE_SPEED); // ricochet limit is zero for sniper
  }
  ++fire_cooldown_timer_;
}

void SniperTank::UpdateShape(float rotation_angle, LevelData &level_data_) {
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