#include "include/Wall.hpp"

Wall::Wall(sf::Vector2f position, sf::Vector2f size)
    : position_(position), size_(size) {

        wallShape_.setPosition(position);
        wallShape_.setSize(size);
        wallShape_.setFillColor(sf::Color::Red);
    }

bool Wall::IsProjectilePassable(){
    return false;
}

bool Wall::IsTankPassable(){
    return false;
}

void Wall::Draw(sf::RenderWindow &window) const {
    window.draw(wallShape_);
}

sf::FloatRect Wall::GetGlobalBounds() const {
  return wallShape_.getGlobalBounds();
}