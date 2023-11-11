#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include "Wall.hpp"

class Projectile {
  public:
    Projectile(sf::Vector2f initial_position, int speed_scaler, float angle, int ricochet_limit);

    bool MoveAndRicochet(const std::vector<Wall> &walls);

    void Draw(sf::RenderWindow &window) const;

  private:
    sf::Vector2f speed_;
    sf::CircleShape projectile_shape_;
    int ricochet_limit_;
    int ricochet_count_ = 0;
};