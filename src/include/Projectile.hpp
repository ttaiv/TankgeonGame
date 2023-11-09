#pragma once
#include "Ordnance.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include "Wall.hpp"

class Projectile: public Ordnance {
  public:
    Projectile(sf::Vector2f initial_position, int speed_scaler, float angle);

    void Update(std::vector<Wall> &walls);

    void Draw(sf::RenderWindow &window) const;

  private:
    sf::Vector2f speed_;
    sf::RectangleShape projectile_shape_;
};