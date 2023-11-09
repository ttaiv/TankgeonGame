#include "include/Spike.hpp"

Spike::Spike(sf::Vector2f position, sf::Vector2f size)
    : position_(position), size_(size) {

        spikeShape_.setPosition(position);
        spikeShape_.setSize(size);
        spikeShape_.setFillColor(sf::Color::Yellow);
    }

bool Spike::IsProjectilePassable(){
    return true;
}

void Spike::Draw(sf::RenderWindow &window) const {
    window.draw(spikeShape_);
}

sf::FloatRect Spike::GetGlobalBounds() const {
  return spikeShape_.getGlobalBounds();
}