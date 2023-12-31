#include "include/Tank.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include "include/Level.hpp"
#include <cmath>

Tank::Tank(sf::Vector2f initial_pos, float speed_scaler, int fire_cooldown) 
  : speed_scaler_(speed_scaler), fire_cooldown_(fire_cooldown) {
      tank_shape_.setOrigin(50, 50);
      tank_shape_.setSize(sf::Vector2f(100,100));
      tank_shape_.setPosition(initial_pos);
      turret_shape_.setOrigin(36,50);
      turret_shape_.setSize(sf::Vector2f(100,100));
      turret_shape_.setPosition(initial_pos);
      shield_shape_.setOrigin(60,60);
      shield_shape_.setRadius(65);
      shield_shape_.setPosition(initial_pos);
      shield_shape_.setFillColor(sf::Color(0,0,0,0));
      explosion_texture_.loadFromFile("../src/assets/explosions/Ex3.png");

      explosion_.setPosition(0,0);
      explosion_.setOrigin(50,50);
      explosion_.setTexture(explosion_texture_);

      fire_sound_buffer_.loadFromFile("../src/assets/sounds/tank_firing.wav");
      explosion_sound_buffer_.loadFromFile("../src/assets/sounds/explosion_sound.wav");
      fire_sound_.setBuffer(fire_sound_buffer_);
      explosion_sound_.setBuffer(explosion_sound_buffer_);


  }

void Tank::SetPosition(sf::Vector2f position) {
  tank_shape_.setPosition(position);
  turret_shape_.setPosition(position);
  shield_shape_.setPosition(position);
}

void Tank::Draw(sf::RenderWindow &window) const {

  window.draw(tank_shape_, getTransform());
  window.draw(turret_shape_);
  window.draw(shield_shape_);
}

void Tank::DrawExplosion(sf::RenderWindow &window){
  if(explosion_sound_.getStatus()!=sf::Sound::Playing) {
    explosion_sound_.play();
  }
  ++explosion_frames_;
  explosion_.setPosition(tank_shape_.getPosition());
  explosion_.setScale(explosion_frames_ * 0.05f, explosion_frames_*0.05f);
  window.draw(explosion_);
  if(explosion_frames_>60){explosion_over_=true;}
}

void Tank::Shoot(float angle, LevelData &level_data_, int ricochet_limit, int projectile_speed) {
  fire_cooldown_timer_ = 0;
  ++shots_fired_;
  Projectile new_projectile(turret_shape_.getPosition(), projectile_speed, angle, ricochet_limit);
  level_data_.projectiles.emplace_back(new_projectile);
  fire_sound_.play();
}

const sf::RectangleShape& Tank::GetShape() const { return tank_shape_; }

bool Tank::IsCollided(sf::Vector2f next_pos, float scaler, const LevelData &level_data_) const {
  sf::RectangleShape tank_shape_copy = tank_shape_;
  tank_shape_copy.setScale(scaler, scaler);
  tank_shape_copy.setPosition(next_pos);
  OBB tankOBB = OBB(tank_shape_copy); 
  
  for (const Wall &wall : level_data_.walls) {
    OBB wallOBB = OBB(wall.GetShape());

    if(tankOBB.collides(wallOBB)) {
      return true;
    }
  }
  for (const Spike &spike : level_data_.spikes) {
    OBB spikeOBB = OBB(spike.GetShape());

    if(tankOBB.collides(spikeOBB)) {
      return true;
    }
  }


  return false;
}

bool Tank::GoForward(float margin, const LevelData &level_data_) {
  float rotation = tank_shape_.getRotation();
  float angleRad = (rotation) * (3.14159265f / 180.0f);
  // Calculate the forward vector
  sf::Vector2f forwardVector(speed_scaler_ * std::cos(angleRad), speed_scaler_ * std::sin(angleRad));

  if (!IsCollided(tank_shape_.getPosition() + forwardVector, margin, level_data_)){
    turret_shape_.move(forwardVector);
    tank_shape_.move(forwardVector);
    shield_shape_.move(forwardVector);
    return true;
  }
  return false;
}

bool Tank::GoBack(float margin, const LevelData &level_data_) {
  float rotation = tank_shape_.getRotation();
  float angleRad = (rotation) * (3.14159265f / 180.0f);

  // Calculate the backward vector
  sf::Vector2f backwardVector(speed_scaler_ * std::cos(angleRad), speed_scaler_ * std::sin(angleRad));
  tank_shape_.move(-backwardVector);
  turret_shape_.move(-backwardVector);
  shield_shape_.move(-backwardVector);

  // Check for collisions after moving backward
  if (!IsCollided(tank_shape_.getPosition(), margin, level_data_)) {
      return true;
  }

  // If collision, revert to the original position
  tank_shape_.move(backwardVector);
  turret_shape_.move(backwardVector);
  shield_shape_.move(backwardVector);
  return false;
}

bool Tank::TurnLeft(float margin, const LevelData &level_data_) {

  sf::Vector2f originalPosition = tank_shape_.getPosition();
  tank_shape_.rotate(2.0f);


  if (IsCollided(tank_shape_.getPosition(), margin, level_data_)) {
    
      tank_shape_.setPosition(originalPosition);
      tank_shape_.rotate(-2.0f);
      return false;
  }
    return true;
}

bool Tank::TurnRight(float margin, const LevelData &level_data_) {

  sf::Vector2f originalPosition = tank_shape_.getPosition();
  tank_shape_.rotate(-2.0f);


  if (IsCollided(tank_shape_.getPosition(), margin, level_data_)) {
    
      tank_shape_.setPosition(originalPosition);
      tank_shape_.rotate(2.0f);
      return false;
  }
    return true;
}

bool Tank::ExplosionAnimationOver() const {return explosion_over_;}

void Tank::SetHitTrue(){is_hit_ = true;}

void Tank::SetHitFalse(){
  is_hit_ = false;
  explosion_frames_=0;
  explosion_over_ = false;
  }

bool Tank::IsHit(){return is_hit_;}

bool Tank::CanShoot() {
  ++frame_counter_; // count frames to keep track of burst cooldown
  ++fire_cooldown_timer_;
  if (frame_counter_ > BURST_COOLDOWN) {
    frame_counter_ = 0;
    shots_fired_ = 0;
  }
  if (fire_cooldown_timer_ > fire_cooldown_ && shots_fired_ < MAX_BURST_PROJECTILES && !is_hit_) {
    return true;
  }
  return false;
}

void Tank::ScaleShape(sf::Vector2u window_size){
  float scaler = std::sqrt(window_size.x * window_size.x + window_size.y * window_size.y);
  tank_shape_.setSize(sf::Vector2f(scaler / 23, scaler / 23));
  turret_shape_.setSize(sf::Vector2f(scaler / 23, scaler / 23));
  tank_shape_.setOrigin((scaler / 23) / 2.0f, (scaler / 23) / 2.0f);
  turret_shape_.setOrigin((scaler / 23) * 0.36, (scaler / 23) / 2.0f );
}

void Tank::ResetCounters() {
  fire_cooldown_timer_ = 0;
  explosion_over_ = false;
  is_hit_ = false;
  explosion_frames_ = 1;
  shots_fired_ = 0;
  frame_counter_ = 0;
}