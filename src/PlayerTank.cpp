#include "include/PlayerTank.hpp"

PlayerTank::PlayerTank(sf::Vector2f initial_pos, float speed_scaler) 
  : Tank(initial_pos, speed_scaler) {}
  
/**
 * @brief Updates tank chassis and turret angles based on inputs. Gets angle to mouse as parameter.
 * 
 * @param rotation_angle 
 */
void PlayerTank::UpdateShape(float rotation_angle) {
  sf::Vector2f current_pos = tank_shape_.getPosition();
  float current_tank_rotation = tank_shape_.getRotation();
  float current_tank_rotation_rad = current_tank_rotation * M_PI / 180.0f;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    sf::Vector2f speed = sf::Vector2f(speed_scaler_ * cos(current_tank_rotation_rad), speed_scaler_ * sin(current_tank_rotation_rad));
    current_pos += speed; 
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    sf::Vector2f speed = sf::Vector2f(speed_scaler_ * cos(current_tank_rotation_rad + M_PI), speed_scaler_ * sin(current_tank_rotation_rad + M_PI));
    current_pos += speed; 
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    current_tank_rotation += 2;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    current_tank_rotation -= 2;
  }

  tank_shape_.setPosition(current_pos);
  tank_shape_.setRotation(current_tank_rotation);
  turret_shape_.setRotation(rotation_angle);
  turret_shape_.setPosition(current_pos);
}


void PlayerTank::Update(sf::RenderWindow &window, std::vector<Projectile> &projectiles) {
  UpdateShape(GetTurretRotationAngle(window) * 180 / M_PI + 180);
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && cooldown_timer_ > 30) {
    cooldown_timer_ = 0;
    Shoot(projectiles, GetTurretRotationAngle(window));
  }
  ++cooldown_timer_;
}

float PlayerTank::GetTurretRotationAngle(sf::RenderWindow &window) { 
  sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
  // We have both the sprite position and the cursor
  // position lets do the calculation so our sprite will
  // face the position of the mouse
  float dx = tank_shape_.getPosition().x - mouse_position.x;
  float dy = tank_shape_.getPosition().y - mouse_position.y;

  return atan2(dy, dx);
}


