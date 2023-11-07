#include "PlayerTank.hpp"

PlayerTank::PlayerTank(sf::Vector2f initial_pos, sf::Vector2f initial_speed) 
  : pos(initial_pos), speed(initial_speed) {
      tankShape.setOrigin(50, 50);
      tankShape.setSize(sf::Vector2f(100,100));
      tankShape.setPosition(pos);
  }

void PlayerTank::UpdatePos() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    pos.x -= speed.x; 
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    pos.x += speed.x; 
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    pos.y -= speed.y; 
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    pos.y += speed.y; 
  }
  tankShape.setPosition(pos);
}

void PlayerTank::Draw(sf::RenderWindow &window) const {
  window.draw(tankShape);
}

void PlayerTank::UpdatePosAndDraw(sf::RenderWindow &window) {
  UpdatePos();
  Draw(window);
}

