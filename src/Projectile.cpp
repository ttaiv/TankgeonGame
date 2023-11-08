#include "include/Projectile.hpp"
#include <iostream>

Projectile::Projectile(sf::Vector2f initial_position, sf::Vector2f speed) :
  pos_(initial_position), speed_(speed) {
    projectile_shape_.setPosition(initial_position);
    projectile_shape_.setOrigin(10, 20);
    projectile_shape_.setSize(sf::Vector2f(20, 40));
  }

void Projectile::Update() {
  pos_ += speed_;
  projectile_shape_.setPosition(pos_);
}

void Projectile::Draw(sf::RenderWindow &window) const {
  window.draw(projectile_shape_);
}