#include "include/Projectile.hpp"
#include <iostream>
#include <math.h>

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

void Projectile::Update() {
  sf::Vector2f newPos = projectile_shape_.getPosition() + speed_;
  projectile_shape_.setPosition(newPos);
}

void Projectile::Draw(sf::RenderWindow &window) const {
  window.draw(projectile_shape_);
}