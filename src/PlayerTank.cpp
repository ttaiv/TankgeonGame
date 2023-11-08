#include "include/PlayerTank.hpp"

PlayerTank::PlayerTank(sf::Vector2f initial_pos, sf::Vector2f initial_speed) 
  : speed_(initial_speed), cooldown_timer_(0) {
      tank_shape_.setOrigin(50, 50);
      tank_shape_.setSize(sf::Vector2f(100,100));
      tank_shape_.setPosition(initial_pos);
  }

void PlayerTank::UpdateShape(float rotation_angle) {
  sf::Vector2f current_pos = tank_shape_.getPosition();
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    current_pos.x -= speed_.x; 
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    current_pos.x += speed_.x; 
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    current_pos.y -= speed_.y; 
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    current_pos.y += speed_.y; 
  }
  tank_shape_.setPosition(current_pos);
  tank_shape_.setRotation(rotation_angle);
}

void PlayerTank::Draw(sf::RenderWindow &window) const {
  window.draw(tank_shape_);
}

void PlayerTank::Update(sf::RenderWindow &window, std::vector<Projectile> &projectiles) {
  UpdateShape(GetRotationAngle(window) * 180 / M_PI + 180);
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && cooldown_timer_ > 30) {
    cooldown_timer_ = 0;
    Shoot(projectiles, GetRotationAngle(window));
  }
  ++cooldown_timer_;
}

float PlayerTank::GetRotationAngle(sf::RenderWindow &window) { 
  sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
  // We have both the sprite position and the cursor
  // position lets do the calculation so our sprite will
  // face the position of the mouse
  float dx = tank_shape_.getPosition().x - mouse_position.x;
  float dy = tank_shape_.getPosition().y - mouse_position.y;

  return atan2(dy, dx);
}

void PlayerTank::Shoot(std::vector<Projectile> &projectiles, float angle) {
  Projectile new_projectile(tank_shape_.getPosition(), 3, angle);
  projectiles.push_back(new_projectile);
}