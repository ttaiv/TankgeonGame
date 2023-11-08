#pragma once
#include "Ordnance.hpp"
#include <SFML/Graphics.hpp>

class Projectile: public Ordnance {
  public:
    Projectile(sf::Vector2f initial_position, int speed_scaler, float angle);

    void Update() override;

    void Draw(sf::RenderWindow &window) const;

  private:
    sf::Vector2f speed_;
    sf::RectangleShape projectile_shape_;
};