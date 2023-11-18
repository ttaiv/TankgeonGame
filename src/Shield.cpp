#include "include/Shield.hpp"

Shield::Shield(sf::Vector2f position) : position_(position) {
  shieldShape_.setPosition(position);
  shieldShape_.setSize(sf::Vector2f(50, 50));
  shieldShape_.setFillColor(sf::Color::Cyan);
}

void Shield::Draw(sf::RenderWindow &window) const {
  window.draw(shieldShape_);
}

sf::RectangleShape Shield::GetShape() const {
  return shieldShape_;
}