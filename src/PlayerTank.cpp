#include "PlayerTank.hpp"

PlayerTank::PlayerTank(sf::Vector2f initial_pos, int initial_speed) 
  : pos(initial_pos), speed(initial_speed) {
      tankShape.setOrigin(50, 50);
      tankShape.setSize(sf::Vector2f(100,100));
      tankShape.setPosition(pos);
  }

void PlayerTank::UpdatePos() {
  pos += sf::Vector2f(speed, speed);
}

void PlayerTank::Draw(sf::RenderWindow &window) const {
  window.draw(tankShape);
}

