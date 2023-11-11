#include "include/Projectile.hpp"
#include <iostream>

Projectile::Projectile(sf::Vector2f initial_position, int speed_scaler, float angle, int ricochet_limit)
  : ricochet_limit_(ricochet_limit) {
    projectile_shape_.setPosition(initial_position);
    projectile_shape_.setRadius(8);
    // projectile_shape_.setRotation(angle * 180 / M_PI);
    projectile_shape_.setFillColor(sf::Color::Yellow);
    projectile_shape_.setOutlineColor(sf::Color::Red);
    projectile_shape_.setOutlineThickness(1);
    
    // Form speed vector using angle
    speed_ = sf::Vector2f(speed_scaler * cos(angle + M_PI), speed_scaler * sin(angle + M_PI));
  }


bool Projectile::MoveAndRicochet(const std::vector<Wall> &walls) {
  projectile_shape_.move(speed_);
  sf::FloatRect projectile_box = projectile_shape_.getGlobalBounds();
  // Check for collision
  for (const Wall &wall : walls) {
    sf::FloatRect wall_bounds = wall.GetShape().getGlobalBounds();
    if (wall_bounds.intersects(projectile_box)) {
      // Collision happened.
      if (ricochet_count_ >= ricochet_limit_) {
        return false; // Projectile should be destroyed
      }
      // Calculate intersection and make projectile ricochet.
      ++ricochet_count_;
      sf::FloatRect intersection;
      wall_bounds.intersects(projectile_box, intersection);
      if (intersection.width > intersection.height) {
        // Collision is more vertical
        speed_.y = -speed_.y;
      } else {
        // Collision is more horizontal
        speed_.x = -speed_.x;
      }
      return true; // Moving and ricochet successful
    }
  }
  return true; // Moving successful;
}

void Projectile::Draw(sf::RenderWindow &window) const {
  window.draw(projectile_shape_);
}
