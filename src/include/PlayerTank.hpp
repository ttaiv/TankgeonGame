#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include "Projectile.hpp"
#include "Tank.hpp"

class PlayerTank: public Tank {
  public:
    PlayerTank(sf::Vector2f initial_pos, sf::Vector2f initial_speed);
    void Update(sf::RenderWindow &window, std::vector<Projectile> &projectiles) override;

  private:
    /**
     * @brief Get new rotation angle for tank shape using mouse position
     * 
     * @param window
     * @return the angle as float
     */
    float GetRotationAngle(sf::RenderWindow &window);
    void UpdateShape(float rotation_angle) override;
};