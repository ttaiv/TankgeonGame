#include "include/Shield.hpp"

Shield::Shield(sf::Vector2f position) : position_(position) {
  shield_shape_.setPosition(position);
  shield_shape_.setSize(sf::Vector2f(100, 100));
  shield_shape_.setFillColor(sf::Color(200,255,255));
  shield_texture.loadFromFile("../src/assets/shield1.png");
  shield_shape_.setTexture(&shield_texture);
}

void Shield::Draw(sf::RenderWindow &window) const {
  window.draw(shield_shape_);
}

sf::RectangleShape Shield::GetShape() const {
  return shield_shape_;
}