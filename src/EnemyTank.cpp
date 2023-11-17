#include "include/EnemyTank.hpp"
#include <cstdlib> 
#include <ctime>  
#include "include/LevelData.hpp" 

EnemyTank::EnemyTank(sf::Vector2f initial_pos, float speed_scaler, LevelData &level_data) 
  : Tank(initial_pos, speed_scaler, level_data) {
      textureNoTurret_.loadFromFile("../src/assets/RedTankNoTurret.png");
      tank_shape_.setTexture(&textureNoTurret_);
      textureTurret_.loadFromFile("../src/assets/RedTankTurret.png");
      turret_shape_.setTexture(&textureTurret_);
  }


void EnemyTank::Update() {
  float angle = GetAngleToPlayer();
  UpdateShape(angle);
  if (cooldown_timer_ > 150 && CanSeePlayer()) {
    cooldown_timer_ = 0;
    Shoot(angle);
  }
  ++cooldown_timer_;
 
}

void EnemyTank::UpdateShape(float rotation_angle) {
  turret_shape_.setRotation(rotation_angle * 180 / M_PI + 180);
  //Introduce randomness
  std::srand(std::time(nullptr) * tank_shape_.getPosition().y);
  double randomFloat = static_cast<double>(std::rand()) / RAND_MAX;
  if (randomFloat < 0.25){
    turnLeft(1);
  }
  else if (randomFloat < 0.50){
    goForward(1.25);
  }
  else if (randomFloat < 0.75){
    goBack(1.25);
  }
  else{
    turnRight(1);
  }
}


float EnemyTank::GetAngleToPlayer() { 
  sf::Vector2f player_position = level_data_.player_.front().getPosition();

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
bool EnemyTank::CanSeePlayer() const {
    sf::Vector2f sightLine = level_data_.player_.front().getPosition() - tank_shape_.getPosition();
    float sightLineLength = std::sqrt(sightLine.x * sightLine.x + sightLine.y * sightLine.y);
    sf::RectangleShape sightLineRect(sf::Vector2f(sightLineLength, 1.0f));
    sightLineRect.setPosition(tank_shape_.getPosition());
    sightLineRect.setRotation(std::atan2(sightLine.y, sightLine.x) * 180.0f / M_PI);
    OBB sightLineOBB = OBB(sightLineRect);

    for (const auto& wall : level_data_.walls_) {
      OBB wallOBB = OBB(wall.GetShape());
        if (sightLineOBB.collides(wallOBB)) {
            return false;
        }
    }
    return true;
}
