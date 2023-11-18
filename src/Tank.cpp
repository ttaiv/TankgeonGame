#include "include/Tank.hpp"
#include "include/LevelData.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>

Tank::Tank(sf::Vector2f initial_pos, float speed_scaler) 
  : speed_scaler_(speed_scaler) {
      tank_shape_.setOrigin(50, 50);
      tank_shape_.setSize(sf::Vector2f(100,100));
      tank_shape_.setPosition(initial_pos);
      turret_shape_.setOrigin(36,50);
      turret_shape_.setSize(sf::Vector2f(100,100));
      turret_shape_.setPosition(initial_pos);
  }


void Tank::Draw(sf::RenderWindow &window) const {
  window.draw(tank_shape_, getTransform());
  window.draw(turret_shape_);
}


void Tank::Shoot(float angle, LevelData &level_data_) {
  Projectile new_projectile(turret_shape_.getPosition(), 6, angle, 1);
  level_data_.projectiles_.push_back(new_projectile);
}

const sf::RectangleShape& Tank::GetShape() const { return tank_shape_; }

bool Tank::IsCollided(sf::Vector2f next_pos, float scaler, LevelData level_data_) const {
  sf::RectangleShape tank_shape_copy = tank_shape_;
  tank_shape_copy.setScale(scaler, scaler);
  tank_shape_copy.setPosition(next_pos);
  OBB tankOBB = OBB(tank_shape_copy); 
  
  for (const Wall &wall : level_data_.walls_) {
    OBB wallOBB = OBB(wall.GetShape());

    if(tankOBB.collides(wallOBB)) {
      return true;
    }
  }
  for (const Spike &spike : level_data_.spikes_) {
    OBB spikeOBB = OBB(spike.GetShape());

    if(tankOBB.collides(spikeOBB)) {
      return true;
    }
  }


  return false;
}

bool Tank::goForward(float margin, LevelData &level_data_) {
  float rotation = tank_shape_.getRotation();
  float angleRad = (rotation) * (3.14159265f / 180.0f);
  // Calculate the forward vector
  sf::Vector2f forwardVector(speed_scaler_ * std::cos(angleRad), speed_scaler_ * std::sin(angleRad));

  if (!IsCollided(tank_shape_.getPosition() + forwardVector, margin, level_data_)){
    turret_shape_.move(forwardVector);
    tank_shape_.move(forwardVector);
    return true;
  }
  return false;
}

bool Tank::goBack(float margin, LevelData &level_data_) {
  float rotation = tank_shape_.getRotation();
  float angleRad = (rotation) * (3.14159265f / 180.0f);

  // Calculate the backward vector
  sf::Vector2f backwardVector(speed_scaler_ * std::cos(angleRad), speed_scaler_ * std::sin(angleRad));
  tank_shape_.move(-backwardVector);
  turret_shape_.move(-backwardVector);

  // Check for collisions after moving backward
  if (!IsCollided(tank_shape_.getPosition(), margin, level_data_)) {
      return true;
  }

  // If collision, revert to the original position
  tank_shape_.move(backwardVector);
  turret_shape_.move(backwardVector);
  return false;
}

bool Tank::turnLeft(float margin, LevelData &level_data_) {

  sf::Vector2f originalPosition = tank_shape_.getPosition();
  tank_shape_.rotate(2.0f);


  if (IsCollided(tank_shape_.getPosition(), margin, level_data_)) {
    
      tank_shape_.setPosition(originalPosition);
      tank_shape_.rotate(-2.0f);
      return false;
  }
    return true;
}

bool Tank::turnRight(float margin, LevelData &level_data_) {

  sf::Vector2f originalPosition = tank_shape_.getPosition();
  tank_shape_.rotate(-2.0f);


  if (IsCollided(tank_shape_.getPosition(), margin, level_data_)) {
    
      tank_shape_.setPosition(originalPosition);
      tank_shape_.rotate(2.0f);
      return false;
  }
    return true;
}


