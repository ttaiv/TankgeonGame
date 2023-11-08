#include "include/PlayerTank.hpp"

PlayerTank::PlayerTank(sf::Vector2f initial_pos, sf::Vector2f initial_speed) 
  : pos_(initial_pos), speed_(initial_speed) {
      tank_shape_.setOrigin(50, 50);
      tank_shape_.setSize(sf::Vector2f(100,100));
      tank_shape_.setPosition(pos_);
  }

void PlayerTank::UpdatePosAndRotation(sf::RenderWindow &window) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    pos_.x -= speed_.x; 
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    pos_.x += speed_.x; 
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    pos_.y -= speed_.y; 
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    pos_.y += speed_.y; 
  }
  tank_shape_.setPosition(pos_);
  tank_shape_.setRotation(GetRotationAngle(window));
}

void PlayerTank::Draw(sf::RenderWindow &window) const {
  window.draw(tank_shape_);
}

void PlayerTank::UpdateAndDraw(sf::RenderWindow &window, std::vector<Projectile> &projectiles) {
  UpdatePosAndRotation(window);
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    Shoot(projectiles);
  }
  Draw(window);
}

float PlayerTank::GetRotationAngle(sf::RenderWindow &window) { 
  sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
  // We have both the sprite position and the cursor
  // position lets do the calculation so our sprite will
  // face the position of the mouse
  float dx = pos_.x - mouse_position.x;
  float dy = pos_.y - mouse_position.y;

  return (atan2(dy, dx)) * 180 / M_PI + 180;
}

void PlayerTank::Shoot(std::vector<Projectile> &projectiles) {
  Projectile new_projectile(pos_, sf::Vector2f(3, 3));
  projectiles.push_back(new_projectile);
}