#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include "Wall.hpp"

class Projectile {
  public:
    Projectile(sf::Vector2f initial_position, int speed_scaler, float angle, int ricochet_limit);

    void Move();
    void RicochetX();
    void RicochetY();
    void Draw(sf::RenderWindow &window) const;
    const sf::CircleShape& GetShape() const;
    int GetRicochetCount() const;
    int GetRicochetLimit() const;
    bool RicochetLimitReached() const;
    bool Hurts() const;

  private:
    sf::Vector2f speed_;
    sf::CircleShape projectile_shape_;
    int ricochet_limit_;
    int ricochet_count_ = 0;
    int lifetime_ = 0;
};