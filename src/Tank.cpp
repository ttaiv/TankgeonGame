#include "include/Tank.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>

Tank::Tank(sf::Vector2f initial_pos, float speed_scaler) 
  : speed_scaler_(speed_scaler), cooldown_timer_(0) {
      tank_shape_.setOrigin(50, 50);
      tank_shape_.setSize(sf::Vector2f(100,100));
      tank_shape_.setPosition(initial_pos);
      turret_shape_.setOrigin(20,20);
      turret_shape_.setSize(sf::Vector2f(40,40));
      turret_shape_.setPosition(tank_shape_.getPosition());
      turret_shape_.setFillColor(sf::Color::Green);
  }


void Tank::Draw(sf::RenderWindow &window) const {
  window.draw(tank_shape_);
  window.draw(turret_shape_);
}


void Tank::Shoot(std::vector<Projectile> &projectiles, float angle) {
  Projectile new_projectile(turret_shape_.getPosition(), 3, angle);
  projectiles.push_back(new_projectile);
}

sf::RectangleShape Tank::GetShape() const { return tank_shape_; }

bool Tank::IsCollided(sf::Vector2f next_pos, std::vector<Wall> &walls, std::vector<Spike> &spikes) const {
  sf::FloatRect tank_bounds = tank_shape_.getGlobalBounds();
  tank_bounds.left = next_pos.x - tank_bounds.width / 2.0f;
  tank_bounds.top = next_pos.y - tank_bounds.height / 2.0f;  
  
  for (Wall &wall : walls) {
    sf::FloatRect wall_bounds = wall.GetGlobalBounds();

    if(tank_bounds.intersects(wall_bounds)) {
      return true;
    }
  }

  for (Spike &spike : spikes) {
    sf::FloatRect spike_bounds = spike.GetGlobalBounds();
    
    if (tank_bounds.intersects(spike_bounds)) {
      return true;
    }
  }

  return false;
}

bool Tank::goForward(std::vector<Wall> &walls, std::vector<Spike> &spikes) {
  sf::Vector2f current_pos = tank_shape_.getPosition();
  float current_tank_rotation = tank_shape_.getRotation();
  float current_tank_rotation_rad = current_tank_rotation * M_PI / 180.0f;
  sf::Vector2f speed = sf::Vector2f(speed_scaler_ * cos(current_tank_rotation_rad), speed_scaler_ * sin(current_tank_rotation_rad));
  current_pos += speed; 
  if (!IsCollided(current_pos, walls, spikes)){
    tank_shape_.setPosition(current_pos);
    turret_shape_.setPosition(current_pos);
    return true;
  } 
  else {
    return false;
  }
}

bool Tank::goBack(std::vector<Wall> &walls, std::vector<Spike> &spikes) {
  sf::Vector2f current_pos = tank_shape_.getPosition();
  float current_tank_rotation = tank_shape_.getRotation();
  float current_tank_rotation_rad = current_tank_rotation * M_PI / 180.0f;
    sf::Vector2f speed = sf::Vector2f(speed_scaler_ * cos(current_tank_rotation_rad + M_PI), speed_scaler_ * sin(current_tank_rotation_rad + M_PI));
    current_pos += speed; 
  if (!IsCollided(current_pos, walls, spikes)){
    tank_shape_.setPosition(current_pos);
    turret_shape_.setPosition(current_pos);
    return true;
  } 
  else {
    return false;
  }
}
void Tank::turnLeft() {
  float current_tank_rotation = tank_shape_.getRotation();
  current_tank_rotation += 2;
  tank_shape_.setRotation(current_tank_rotation);
}
void Tank::turnRight() {
  float current_tank_rotation = tank_shape_.getRotation();
  current_tank_rotation -= 2;
  tank_shape_.setRotation(current_tank_rotation);
}


