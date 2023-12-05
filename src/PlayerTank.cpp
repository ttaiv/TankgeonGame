#include "include/PlayerTank.hpp"
#include "include/Level.hpp"

PlayerTank::PlayerTank(sf::Vector2f initial_pos, float speed_scaler) 
  : Tank(initial_pos, speed_scaler, PLAYER_FIRE_COOLDOWN) {
      chassis_texture_.loadFromFile("../src/assets/tanks/TankNoTurret.png");
      tank_shape_.setTexture(&chassis_texture_);
      turret_texture_.loadFromFile("../src/assets/tanks/TankTurret.png");
      turret_shape_.setTexture(&turret_texture_);
      shield_texture_.loadFromFile("../src/assets/ShieldEffect.png");
      shield_shape_.setTexture(&shield_texture_);
      has_shield_ = false;
      score_ = 0;
  }
  
/**
 * @brief Updates tank chassis and turret angles based on inputs. Gets angle to mouse as parameter.
 * 
 * @param rotation_angle 
 */
void PlayerTank::UpdateShape(float rotation_angle, LevelData &level_data) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    GoForward(1, level_data);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    GoBack(1,level_data);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    TurnLeft(1, level_data);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    TurnRight(1, level_data);
  }

  turret_shape_.setRotation(rotation_angle);
}


void PlayerTank::Update(sf::RenderWindow &window, LevelData &level_data) {
  UpdateShape(GetTurretRotationAngle(window) * 180 / M_PI + 180, level_data);
  bool can_shoot = CanShoot(); // important to call every frame
  if (can_shoot && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    Shoot(GetTurretRotationAngle(window), level_data, NORMAL_RICOCHET_COUNT, BASE_PROJECTILE_SPEED);
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

void PlayerTank::SetShield() {
  has_shield_ = true;
  shield_shape_.setFillColor(sf::Color(0,0,255,255));
}

void PlayerTank::BreakShield() {
  has_shield_ = false;
  shield_shape_.setFillColor(sf::Color::Transparent);
}

bool PlayerTank::HasShield() const {
  return has_shield_;
}

void PlayerTank::AddScore(int amount){
  score_ += amount;
}

int PlayerTank::GetScore() const {
  return score_;
}

void PlayerTank::ResetScore() {
  score_ = 0;
}



