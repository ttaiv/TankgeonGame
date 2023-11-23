#include "include/SniperTank.hpp"

SniperTank::SniperTank(sf::Vector2f initial_pos, PlayerTank &player)
  : EnemyTank(initial_pos, SNIPER_TANK_SPEED, player) {
    chassis_texture_.loadFromFile("../src/assets/tanks/RedTankNoTurret.png");
    tank_shape_.setTexture(&chassis_texture_);
    turret_texture_.loadFromFile("../src/assets/tanks/RedTankTurret.png");
    turret_shape_.setTexture(&turret_texture_);
  }
SniperTank::SniperTank(const SniperTank &other)
    : EnemyTank(other), chassis_texture_(other.chassis_texture_), turret_texture_(other.turret_texture_) {
    // Reload textures for the new object
    tank_shape_.setTexture(&chassis_texture_);
    turret_shape_.setTexture(&turret_texture_);
}

void SniperTank::Update(LevelData &level_data_) {
  float angle = GetAngleToPlayer();
  UpdateShape(angle, level_data_);
  if (cooldown_timer_ > 150 && CanSeePlayer(level_data_)) {
    cooldown_timer_ = 0;
    Shoot(angle, level_data_, 0, SNIPER_PROJECTILE_SPEED); // ricochet limit is zero for sniper
  }
  ++cooldown_timer_;
}

void SniperTank::UpdateShape(float rotation_angle, LevelData &level_data_) {
  turret_shape_.setRotation(rotation_angle * 180 / M_PI + 180);
  //Introduce randomness
  std::srand(std::time(nullptr));
  double randomFloat = static_cast<double>(std::rand()) / RAND_MAX;
  
  if (randomFloat < 0.25){
    turnLeft(1, level_data_);
  }
  else if (randomFloat < 0.50){
    goForward(2, level_data_);
  }
  else if (randomFloat < 0.75){
    goBack(2, level_data_);
  }
  else{
    turnRight(1, level_data_);
  }
}