#include "include/Spike.hpp"

Spike::Spike(sf::Vector2f position, sf::Vector2f size)
    : position_(position), size_(size) {

        spikeShape_.setPosition(position);
        spikeShape_.setSize(size);
        spikeShape_.setFillColor(sf::Color::Yellow);
        spikeTexture_.loadFromFile("../src/assets/Hole.png");
        spikeShape_.setTexture(&spikeTexture_);
        sf::Vector2i hitbox_size = sf::Vector2i(static_cast<int>(std::round(size.x)), static_cast<int>(std::round(size.y))); 
        sf::Vector2i hitbox_position = sf::Vector2i(static_cast<int>(std::round(position.x)), static_cast<int>(std::round(position.y)));
        spikeShape_.setTextureRect({ hitbox_position, hitbox_size });
        spikeTexture_.setRepeated(true);

    }

Spike::Spike(const Spike &other) : position_(other.position_), size_(other.size_){
    spikeShape_.setPosition(other.position_);
    spikeShape_.setSize(other.size_);
    spikeShape_.setFillColor(sf::Color::Yellow);
    spikeTexture_.loadFromFile("../src/assets/Hole.png");
    spikeShape_.setTexture(&spikeTexture_);
    spikeTexture_.setRepeated(true);
    sf::Vector2i hitbox_size = sf::Vector2i(static_cast<int>(std::round(other.size_.x)), static_cast<int>(std::round(other.size_.y))); 
    sf::Vector2i hitbox_position = sf::Vector2i(static_cast<int>(std::round(other.position_.x)), static_cast<int>(std::round(other.position_.y)));
    spikeShape_.setTextureRect({ hitbox_position, hitbox_size });
}

/*
Spike& Spike::operator=(const Spike &other){
    if(this != &other){
    position_ = other.position_;
    size_ = other.size_;
    spikeShape_.setPosition(other.position_);
    spikeShape_.setSize(other.size_);
    spikeShape_.setFillColor(sf::Color::Yellow);
    spikeTexture_.loadFromFile("../src/assets/Hole.png");
    spikeTexture_.setRepeated(true);
    spikeShape_.setTexture(&spikeTexture_);
    // spikeShape_.setTextureRect( {1180,550, 280, 600} );
    }
    return *this;
}
*/

bool Spike::IsProjectilePassable(){
    return true;
}

void Spike::Draw(sf::RenderWindow &window) const {
    window.draw(spikeShape_);
}

sf::FloatRect Spike::GetGlobalBounds() const {
  return spikeShape_.getGlobalBounds();
}