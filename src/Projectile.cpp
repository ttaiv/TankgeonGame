#include "include/Projectile.hpp"
#include <iostream>

Projectile::Projectile(sf::Vector2f initial_position, int speed_scaler, float angle) {
  projectile_shape_.setPosition(initial_position);
  projectile_shape_.setOrigin(10, 5);
  projectile_shape_.setSize(sf::Vector2f(20, 10));
  projectile_shape_.setRotation(angle * 180 / M_PI);
  projectile_shape_.setFillColor(sf::Color::Yellow);
  projectile_shape_.setOutlineColor(sf::Color::Red);
  projectile_shape_.setOutlineThickness(1);
  
  // Form speed vector using angle
  speed_ = sf::Vector2f(speed_scaler * cos(angle + M_PI), speed_scaler * sin(angle + M_PI));
}

void Projectile::Update(std::vector<Wall> &walls) {
  sf::Vector2f current_pos = projectile_shape_.getPosition();
  /*
  for (Wall &wall : walls) {
    sf::FloatRect wall_bounds = wall.GetGlobalBounds();
    if (current_pos.x >= wall_bounds.left || current_pos.x <= wall_bounds.left + wall_bounds.width) {
      speed_.x = - speed_.x;
      break;
    }
    else if (current_pos.y >= wall_bounds.top || current_pos.y <= wall_bounds.top + wall_bounds.height) {
      speed_.y = - speed_.y;
      break;
    }
  }
  */
  projectile_shape_.setPosition(current_pos + speed_);
}

void Projectile::Draw(sf::RenderWindow &window) const {
  window.draw(projectile_shape_);
}