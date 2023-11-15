#include "include/Tank.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>

Tank::Tank(sf::Vector2f initial_pos, float speed_scaler) 
  : speed_scaler_(speed_scaler), cooldown_timer_(0) {
      tank_shape_.setOrigin(50, 50);
      tank_shape_.setSize(sf::Vector2f(100,100));
      tank_shape_.setPosition(initial_pos);
      turret_shape_.setOrigin(36,50);
      turret_shape_.setSize(sf::Vector2f(100,100));
      turret_shape_.setPosition(tank_shape_.getPosition().x-18,tank_shape_.getPosition().y+2);
  }


void Tank::Draw(sf::RenderWindow &window) const {
  window.draw(tank_shape_);
  window.draw(turret_shape_);
}


void Tank::Shoot(std::vector<Projectile> &projectiles, float angle) {
  Projectile new_projectile(turret_shape_.getPosition(), 4, angle, 1);
  projectiles.push_back(new_projectile);
}

const sf::RectangleShape& Tank::GetShape() const { return tank_shape_; }

bool Tank::IsCollided(sf::Vector2f next_pos, const std::vector<Wall> &walls, const std::vector<Spike> &spikes, float scaler) const {
  sf::RectangleShape tank_shape_copy = tank_shape_;
  tank_shape_copy.setScale(scaler, scaler);
  sf::FloatRect tank_bounds = tank_shape_copy.getGlobalBounds();
  tank_bounds.left = next_pos.x - tank_bounds.width / 2.0f;
  tank_bounds.top = next_pos.y - tank_bounds.height / 2.0f;  
  
  for (const Wall &wall : walls) {
    sf::FloatRect wall_bounds = wall.GetShape().getGlobalBounds();

    if(tank_bounds.intersects(wall_bounds)) {
      return true;
    }
  }

  for (const Spike &spike : spikes) {
    sf::FloatRect spike_bounds = spike.GetGlobalBounds();
    
    if (tank_bounds.intersects(spike_bounds)) {
      return true;
    }
  }

  return false;
}

bool Tank::goForward(const std::vector<Wall> &walls, const std::vector<Spike> &spikes, float margin) {
  sf::Vector2f current_pos = tank_shape_.getPosition();
  float current_tank_rotation = tank_shape_.getRotation();
  float current_tank_rotation_rad = current_tank_rotation * M_PI / 180.0f;
  sf::Vector2f speed = sf::Vector2f(speed_scaler_ * cos(current_tank_rotation_rad), speed_scaler_ * sin(current_tank_rotation_rad));
  current_pos += speed; 
  if (!IsCollided(current_pos, walls, spikes, margin)){
    tank_shape_.setPosition(current_pos);
    turret_shape_.setPosition(current_pos);
    return true;
  } 
  else {
    return false;
  }
}

bool Tank::goBack(const std::vector<Wall> &walls, const std::vector<Spike> &spikes, float margin) {
  sf::Vector2f current_pos = tank_shape_.getPosition();
  float current_tank_rotation = tank_shape_.getRotation();
  float current_tank_rotation_rad = current_tank_rotation * M_PI / 180.0f;
    sf::Vector2f speed = sf::Vector2f(speed_scaler_ * cos(current_tank_rotation_rad + M_PI), speed_scaler_ * sin(current_tank_rotation_rad + M_PI));
    current_pos += speed; 
  if (!IsCollided(current_pos, walls, spikes, margin)){
    tank_shape_.setPosition(current_pos);
    turret_shape_.setPosition(current_pos);
    return true;
  } 
  else {
    return false;
  }
}

bool Tank::turnLeft(const std::vector<Wall> &walls, const std::vector<Spike> &spikes, float margin) {
  float current_tank_rotation = tank_shape_.getRotation();
  current_tank_rotation += 2;
  float original_rotation_input = current_tank_rotation;
  tank_shape_.setRotation(current_tank_rotation);
  
  
  /*Check if rotation causes a collision.
  If a collision is detected the turn is reduced
  so that a collision wont occur*/
  if (IsCollided(tank_shape_.getPosition(), walls, spikes, margin)) {
    float adjusted_rotation = current_tank_rotation;
    while (IsCollided(tank_shape_.getPosition(), walls, spikes, margin) && ((original_rotation_input - adjusted_rotation) <= 2)) {
      adjusted_rotation -= 0.1f;
      tank_shape_.setRotation(adjusted_rotation);
    }
    current_tank_rotation = adjusted_rotation;
    return false;
  }
  else {
    return true; 
  }
}

bool Tank::turnRight(const std::vector<Wall> &walls, const std::vector<Spike> &spikes, float margin) {
  float current_tank_rotation = tank_shape_.getRotation();
  current_tank_rotation -= 2;
  float original_rotation_input = current_tank_rotation;
  tank_shape_.setRotation(current_tank_rotation);
  
  /*Check if rotation causes a collision.
  If a collision is detected the turn is reduced
  so that a collision wont occur*/
  if (IsCollided(tank_shape_.getPosition(), walls, spikes, margin)) {
    float adjusted_rotation = current_tank_rotation;
    while (IsCollided(tank_shape_.getPosition(), walls, spikes, margin) && ((adjusted_rotation - original_rotation_input) <= 2)) {
      adjusted_rotation += 0.1f;
      tank_shape_.setRotation(adjusted_rotation);
    }
    current_tank_rotation = adjusted_rotation;
    return false;
  }
  else {
    return true;
  }
}


