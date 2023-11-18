#include "include/PlayerTank.hpp"

PlayerTank::PlayerTank(sf::Vector2f initial_pos, float speed_scaler) 
  : Tank(initial_pos, speed_scaler) {
      textureNoTurret_.loadFromFile("../src/assets/TankNoTurret.png");
      tank_shape_.setTexture(&textureNoTurret_);
      textureTurret_.loadFromFile("../src/assets/TankTurret.png");
      turret_shape_.setTexture(&textureTurret_);
      has_shield_ = false;
  }
  
/**
 * @brief Updates tank chassis and turret angles based on inputs. Gets angle to mouse as parameter.
 * 
 * @param rotation_angle 
 */
void PlayerTank::UpdateShape(float rotation_angle, std::vector<Wall> &walls, std::vector<Spike> &spikes) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    goForward(walls, spikes, 1);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    goBack(walls, spikes, 1);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    turnLeft(walls, spikes, 1);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    turnRight(walls, spikes, 1);
  }

  turret_shape_.setRotation(rotation_angle);
}


void PlayerTank::Update(sf::RenderWindow &window, std::vector<Projectile> &projectiles, std::vector<Wall> &walls, std::vector<Spike> &spikes) {
  UpdateShape(GetTurretRotationAngle(window) * 180 / M_PI + 180, walls, spikes);
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

void PlayerTank::setShield() {
  has_shield_ = true;
}

void PlayerTank::breakShield() {
  has_shield_ = false;
}

bool PlayerTank::hasShield() const {
  return has_shield_;
}



