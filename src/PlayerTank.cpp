#include "include/PlayerTank.hpp"

PlayerTank::PlayerTank(sf::Vector2f initial_pos, sf::Vector2f initial_speed) 
  : pos(initial_pos), speed(initial_speed) {
      tankShape.setOrigin(50, 50);
      tankShape.setSize(sf::Vector2f(100,100));
      tankShape.setPosition(pos);
  }

void PlayerTank::UpdatePosAndRotation(sf::RenderWindow &window) {
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
  tankShape.setRotation(GetRotationAngle(window));
}

void PlayerTank::Draw(sf::RenderWindow &window) const {
  window.draw(tankShape);
}

void PlayerTank::UpdateAndDraw(sf::RenderWindow &window) {
  UpdatePosAndRotation(window);
  Draw(window);
}

float PlayerTank::GetRotationAngle(sf::RenderWindow &window) { 
  sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
  // We have both the sprite position and the cursor
  // position lets do the calculation so our sprite will
  // face the position of the mouse
  float dx = pos.x - mouse_position.x;
  float dy = pos.y - mouse_position.y;

  return (atan2(dy, dx)) * 180 / M_PI + 180;
}

