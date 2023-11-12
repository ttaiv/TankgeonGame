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


void Projectile::Move() {
  ++lifetime_;
  projectile_shape_.move(speed_);
}

void Projectile::RicochetX() {
  ++ricochet_count_;
  speed_.x = -speed_.x;
}

void Projectile::RicochetY() {
  ++ricochet_count_;
  speed_.y = -speed_.y;
}

const sf::CircleShape& Projectile::GetShape() const {
  return projectile_shape_;
}

int Projectile::GetRicochetCount() const {
  return ricochet_count_;
}

int Projectile::GetRicochetLimit() const {
  return ricochet_limit_;
}

bool Projectile::RicochetLimitReached() const {
  return ricochet_count_ >= ricochet_limit_;
}

void Projectile::Draw(sf::RenderWindow &window) const {
  window.draw(projectile_shape_);
}

bool Projectile::Hurts() const {
  return lifetime_ > 30;
}
