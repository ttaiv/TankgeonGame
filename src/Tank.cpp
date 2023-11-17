#include "include/Tank.hpp"
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


void Tank::Shoot(std::vector<Projectile> &projectiles, float angle) {
  Projectile new_projectile(turret_shape_.getPosition(), 6, angle, 1);
  projectiles.push_back(new_projectile);
}

const sf::RectangleShape& Tank::GetShape() const { return tank_shape_; }

bool Tank::IsCollided(sf::Vector2f next_pos, const std::vector<Wall> &walls, const std::vector<Spike> &spikes, float scaler) const {
  sf::RectangleShape tank_shape_copy = tank_shape_;
  tank_shape_copy.setScale(scaler, scaler);
  tank_shape_copy.setPosition(next_pos);
  OBB tankOBB = OBB(tank_shape_copy); 
  
  for (const Wall &wall : walls) {
    OBB wallOBB = OBB(wall.GetShape());

    if(tankOBB.collides(wallOBB)) {
      return true;
    }
  }
  for (const Spike &spike : spikes) {
    OBB spikeOBB = OBB(spike.GetShape());

    if(tankOBB.collides(spikeOBB)) {
      return true;
    }
  }


  return false;
}

bool Tank::goForward(const std::vector<Wall>& walls, const std::vector<Spike>& spikes, float margin) {
  float rotation = tank_shape_.getRotation();
  float angleRad = (rotation) * (3.14159265f / 180.0f);
  // Calculate the forward vector
  sf::Vector2f forwardVector(speed_scaler_ * std::cos(angleRad), speed_scaler_ * std::sin(angleRad));

  if (!IsCollided(tank_shape_.getPosition() + forwardVector, walls, spikes, margin)) {
    tank_shape_.move(forwardVector);
    turret_shape_.move(forwardVector);
    return true;
  }
  return false;
}

bool Tank::goBack(const std::vector<Wall> &walls, const std::vector<Spike> &spikes, float margin) {
  float rotation = tank_shape_.getRotation();
  float angleRad = (rotation) * (3.14159265f / 180.0f);

  // Calculate the backward vector
  sf::Vector2f backwardVector(speed_scaler_ * std::cos(angleRad), speed_scaler_ * std::sin(angleRad));
  tank_shape_.move(-backwardVector);
  turret_shape_.move(-backwardVector);

  // Check for collisions after moving backward
  if (!IsCollided(tank_shape_.getPosition(), walls, spikes, margin)) {
      return true;
  }

  // If collision, revert to the original position
  tank_shape_.move(backwardVector);
  turret_shape_.move(backwardVector);
  return false;
}

bool Tank::turnLeft(const std::vector<Wall> &walls, const std::vector<Spike> &spikes, float margin) {
  if (!IsCollided(tank_shape_.getPosition(), walls, spikes, margin)){
    tank_shape_.rotate(2.f);
    return true;
  }
  return false;
}

bool Tank::turnRight(const std::vector<Wall> &walls, const std::vector<Spike> &spikes, float margin) {
  // Save the current position and rotation
  sf::Vector2f originalPosition = tank_shape_.getPosition();

  // Rotate the tank to the right
  tank_shape_.rotate(-2.0f);

  // Check for collisions after rotation
  if (IsCollided(tank_shape_.getPosition(), walls, spikes, margin)) {
      // If collision, revert to the original position and rotation
      tank_shape_.setPosition(originalPosition);
      tank_shape_.rotate(2.0f);
      return false;
  }

    // If no collision, rotation is successful
    return true;
}


