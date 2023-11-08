#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Obstacle {
  public:
    virtual bool IsProjectilePassable() = 0;
    virtual bool IsTankPassable() = 0;
  private:
    sf::RectangleShape shape_;
    
};

