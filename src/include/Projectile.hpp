#pragma once
#include "Ordnance.hpp"
#include <SFML/Graphics.hpp>

class Projectile: public Ordnance {
  public:
    Projectile(sf::Vector2f initial_position, sf::Vector2f speed);

    void Update() override;

    void Draw(sf::RenderWindow &window) const;

  private:
    sf::Vector2f pos_;
    sf::Vector2f speed_;
    sf::RectangleShape projectile_shape_;
};