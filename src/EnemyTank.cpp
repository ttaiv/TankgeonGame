#include "include/EnemyTank.hpp"

EnemyTank::EnemyTank(sf::Vector2f initial_pos, float speed_scaler) 
  : Tank(initial_pos, speed_scaler) {
      textureNoTurret_.loadFromFile("../src/assets/RedTankNoTurret.png");
      tank_shape_.setTexture(&textureNoTurret_);
      textureTurret_.loadFromFile("../src/assets/RedTankTurret.png");
      turret_shape_.setTexture(&textureTurret_);
  }

/*
EnemyTank::EnemyTank(const EnemyTank &other) 
  : Tank(other) {
    textureNoTurret_.loadFromFile("../src/assets/RedTankNoTurret.png");
    tank_shape_.setTexture(&textureNoTurret_);
    textureTurret_.loadFromFile("../src/assets/RedTankTurret.png");
    turret_shape_.setTexture(&textureTurret_);
  }

EnemyTank& EnemyTank::operator=(const EnemyTank &other) {
  if (this != &other) {
    Tank::operator=(other); // call (default) copy assignment operator of Tank
    textureNoTurret_.loadFromFile("../src/assets/RedTankNoTurret.png");
    tank_shape_.setTexture(&textureNoTurret_);
    textureTurret_.loadFromFile("../src/assets/RedTankTurret.png");
    turret_shape_.setTexture(&textureTurret_);
  }
  return *this;
}
*/

void EnemyTank::Update(std::vector<Projectile> &projectiles, const sf::RectangleShape &player_tank, const std::vector<Wall> &walls, const std::vector<Spike> &spikes) {
  float angle = GetAngleToPlayer(player_tank);
  UpdateShape(angle, walls, spikes, projectiles);
  if (cooldown_timer_ > 150) {
    cooldown_timer_ = 0;
    Shoot(projectiles, angle);
  }
  ++cooldown_timer_;
 
}

void EnemyTank::UpdateShape(float rotation_angle, const std::vector<Wall> &walls, const std::vector<Spike> &spikes, const std::vector<Projectile> &projectiles) {
  turret_shape_.setRotation(rotation_angle * 180 / M_PI + 180);
  if (!WillBeHit(projectiles)){
    if (!goForward(walls, spikes, 2)) {
     turnLeft(walls, spikes, 1);  
   }
  }
  else{
    goBack(walls, spikes, 1);
  }
}


float EnemyTank::GetAngleToPlayer(sf::RectangleShape player_tank) { 
  sf::Vector2f player_position = player_tank.getPosition();

  float dx = turret_shape_.getPosition().x - player_position.x;
  float dy = turret_shape_.getPosition().y - player_position.y;

  return atan2(dy, dx);
}

bool EnemyTank::WillBeHit(const std::vector<Projectile> &projectiles) const {
  float predictionTime = 1.0;
  float AvoidanceRadius = 100.0;
  for (const auto &it : projectiles) {
    sf::Vector2f futureProjectilePosition = it.GetShape().getPosition() + it.GetSpeed() * predictionTime;
    sf::Vector2f diff = tank_shape_.getPosition() - futureProjectilePosition;
      if (std::sqrt(diff.x * diff.x + diff.y * diff.y) < AvoidanceRadius && it.Hurts()) {
        return true;
    }
  }
  return false;
}

