#pragma once
#include "Ordnance.hpp"
#include <SFML/Graphics.hpp>

class Projectile: public Ordnance {
  public:
    

  private:
    sf::Vector2f pos_;
    sf::Vector2f speed_;
    sf::RectangleShape projectile_shape_;
};