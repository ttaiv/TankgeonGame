#include "include/EnemyTank.hpp"
#include <cstdlib> 
#include <ctime>  
#include "include/Level.hpp" 

EnemyTank::EnemyTank(sf::Vector2f initial_pos, float speed_scaler, PlayerTank &player) 
  : Tank(initial_pos, speed_scaler), player_(player)  {
      textureNoTurret_.loadFromFile("../src/assets/RedTankNoTurret.png");
      tank_shape_.setTexture(&textureNoTurret_);
      textureTurret_.loadFromFile("../src/assets/RedTankTurret.png");
      turret_shape_.setTexture(&textureTurret_);
}
EnemyTank::EnemyTank(const EnemyTank &other)
    : Tank(other), textureNoTurret_(other.textureNoTurret_), textureTurret_(other.textureTurret_), player_(other.player_) {
    // Reload textures for the new object
    tank_shape_.setTexture(&textureNoTurret_);
    turret_shape_.setTexture(&textureTurret_);
}


void EnemyTank::Update(LevelData &level_data_) {
  float angle = GetAngleToPlayer();
  UpdateShape(angle, level_data_);
  if (cooldown_timer_ > 150 && CanSeePlayer(level_data_)) {
    cooldown_timer_ = 0;
    Shoot(angle, level_data_);
  }
  ++cooldown_timer_;
 
}

void EnemyTank::UpdateShape(float rotation_angle, LevelData &level_data_) {
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


float EnemyTank::GetAngleToPlayer() { 
  sf::Vector2f player_position = player_.GetShape().getPosition();
  float dx = turret_shape_.getPosition().x - player_position.x;
  float dy = turret_shape_.getPosition().y - player_position.y;
  return atan2(dy, dx);
}

/*
bool EnemyTank::WillBeHit() const {
  float predictionTime = 100.0;
  float AvoidanceRadius = 1000.0;
  for (const auto &it : projectiles) {
    sf::Vector2f futureProjectilePosition = it.GetShape().getPosition() + it.GetSpeed() * predictionTime;
    sf::Vector2f diff = tank_shape_.getPosition() - futureProjectilePosition;
      if (std::sqrt(diff.x * diff.x + diff.y * diff.y) < AvoidanceRadius && it.Hurts()) {
        return true;
    }
  }
  return false;
}
*/
bool EnemyTank::CanSeePlayer(LevelData &level_data_) const {
    sf::Vector2f sightLine = player_.GetShape().getPosition() - tank_shape_.getPosition();
    float sightLineLength = std::sqrt(sightLine.x * sightLine.x + sightLine.y * sightLine.y);
    sf::RectangleShape sightLineRect(sf::Vector2f(sightLineLength, 1.0f));
    sightLineRect.setPosition(tank_shape_.getPosition());
    sightLineRect.setRotation(std::atan2(sightLine.y, sightLine.x) * 180.0f / M_PI);
    OBB sightLineOBB = OBB(sightLineRect);

    for (const auto& wall : level_data_.walls) {
      OBB wallOBB = OBB(wall.GetShape());
        if (sightLineOBB.collides(wallOBB)) {
            return false;
        }
    }
    return true;
}
