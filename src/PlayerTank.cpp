#include "include/PlayerTank.hpp"
#include "include/Level.hpp"

PlayerTank::PlayerTank(sf::Vector2f initial_pos, float speed_scaler) 
  : Tank(initial_pos, speed_scaler) {
      chassis_texture_.loadFromFile("../src/assets/tanks/TankNoTurret.png");
      tank_shape_.setTexture(&chassis_texture_);
      turret_texture_.loadFromFile("../src/assets/tanks/TankTurret.png");
      turret_shape_.setTexture(&turret_texture_);
      shieldTexture_.loadFromFile("../src/assets/ShieldEffect.png");
      shield_shape_.setTexture(&shieldTexture_);
      has_shield_ = false;
  }
  
/**
 * @brief Updates tank chassis and turret angles based on inputs. Gets angle to mouse as parameter.
 * 
 * @param rotation_angle 
 */
void PlayerTank::UpdateShape(float rotation_angle, LevelData &level_data) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    goForward(1, level_data);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    goBack(1,level_data);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    turnLeft(1, level_data);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    turnRight(1, level_data);
  }

  turret_shape_.setRotation(rotation_angle);
}


void PlayerTank::Update(sf::RenderWindow &window, LevelData &level_data) {
  UpdateShape(GetTurretRotationAngle(window) * 180 / M_PI + 180, level_data);
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && cooldown_timer_ > FIRE_COOLDOWN) {
    cooldown_timer_ = 0;
    if (shots_fired_ < MAX_BURST_PROJECTILES) {
      Shoot(GetTurretRotationAngle(window), level_data, 1, BASE_PROJECTILE_SPEED);
      ++shots_fired_;
    }
  }
  ++cooldown_timer_;
  ++frame_counter_;
  if (frame_counter_ > BURST_COOLDOWN) {
    frame_counter_ = 0;
    shots_fired_ = 0;
  }
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

void PlayerTank::setShield() {
  has_shield_ = true;
  shield_shape_.setFillColor(sf::Color(0,0,255,255));
}

void PlayerTank::breakShield() {
  has_shield_ = false;
  shield_shape_.setFillColor(sf::Color::Transparent);
}

bool PlayerTank::hasShield() const {
  return has_shield_;
}



