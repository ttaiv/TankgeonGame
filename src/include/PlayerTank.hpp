#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include "Projectile.hpp"

class PlayerTank {
  public:
    PlayerTank(sf::Vector2f initial_pos, sf::Vector2f initial_speed);

    void UpdateShape(float rotation_angle);
    void Draw(sf::RenderWindow &window) const ;
    void Update(sf::RenderWindow &window, std::vector<Projectile> &projectiles);
    void Shoot(std::vector<Projectile> &projectiles, float angle);

  private:
    sf::Vector2f speed_;
    sf::RectangleShape tank_shape_;
    int cooldown_timer_;
    /**
     * @brief Get new rotation angle for tank shape using mouse position
     * 
     * @param window
     * @return the angle as float
     */
    float GetRotationAngle(sf::RenderWindow &window);

};