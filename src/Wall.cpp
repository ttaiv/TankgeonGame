#include "include/Wall.hpp"

Wall::Wall(sf::Vector2f position, sf::Vector2f size) : position_(position), size_(size) {
  wallShape_.setPosition(position);
  wallShape_.setSize(size);
  wallShape_.setFillColor(sf::Color::White);
  wallTexture_.loadFromFile("../src/assets/Wall.jpg");
  wallShape_.setTexture(&wallTexture_);
  wallTexture_.setRepeated(true); //does not repeat hmm...?
}

Wall::Wall(const Wall &other) : position_(other.position_), size_(other.size_) {
  wallShape_.setPosition(other.position_);
  wallShape_.setSize(other.size_);
  wallShape_.setFillColor(sf::Color::White);
  wallTexture_.loadFromFile("../src/assets/Wall.jpg");
  wallShape_.setTexture(&wallTexture_);
  wallTexture_.setRepeated(true); //does not repeat hmm...?
}

Wall& Wall::operator=(const Wall &other) {
  if (this != &other) {
    position_ = other.position_;
    size_ = other.size_;
    wallShape_.setPosition(other.position_);
    wallShape_.setSize(other.size_);
    wallShape_.setFillColor(sf::Color::White);
    wallTexture_.loadFromFile("../src/assets/Wall.jpg");
    wallShape_.setTexture(&wallTexture_);
    wallTexture_.setRepeated(true); //does not repeat hmm...?
  }
  return *this;
}

bool Wall::IsProjectilePassable(){
  return false;
}

void Wall::Draw(sf::RenderWindow &window) const {
  window.draw(wallShape_);
}

sf::RectangleShape Wall::GetShape() const {
  return wallShape_;
}