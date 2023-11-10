#include "include/Projectile.hpp"
#include <iostream>

Projectile::Projectile(sf::Vector2f initial_position, int speed_scaler, float angle) {
  projectile_shape_.setPosition(initial_position);
  projectile_shape_.setRadius(8);
  // projectile_shape_.setRotation(angle * 180 / M_PI);
  projectile_shape_.setFillColor(sf::Color::Yellow);
  projectile_shape_.setOutlineColor(sf::Color::Red);
  projectile_shape_.setOutlineThickness(1);
  
  // Form speed vector using angle
  speed_ = sf::Vector2f(speed_scaler * cos(angle + M_PI), speed_scaler * sin(angle + M_PI));
}

void Projectile::Update(std::vector<Wall> &walls) {
  // Update position
  projectile_shape_.move(speed_);
  // Check for collision
  for (Wall &wall : walls) {
    sf::FloatRect wall_bounds = wall.GetShape().getGlobalBounds();
    sf::FloatRect projectile_box = projectile_shape_.getGlobalBounds();
    if (wall_bounds.intersects(projectile_box)) {
      // Collision happened, calculate intersection and make projectile bounce.
      sf::FloatRect intersection;
      wall_bounds.intersects(projectile_box, intersection);
      if (intersection.width > intersection.height) {
        // Collision is more vertical
        speed_.y = -speed_.y;
      } else {
        // Collision is more horizontal
        speed_.x = -speed_.x;
      }
      break;
    }
  }
}

void Projectile::Draw(sf::RenderWindow &window) const {
  window.draw(projectile_shape_);
}