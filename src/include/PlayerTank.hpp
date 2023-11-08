#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include "Projectile.hpp"

class PlayerTank {
  public:
    PlayerTank(sf::Vector2f initial_pos, sf::Vector2f initial_speed);

    void UpdatePosAndRotation(sf::RenderWindow &window);
    void Draw(sf::RenderWindow &window) const ;
    void UpdateAndDraw(sf::RenderWindow &window, std::vector<Projectile> &projectiles);
    void Shoot(std::vector<Projectile> &projectiles);

  private:
    sf::Vector2f pos_;
    sf::Vector2f speed_;
    sf::RectangleShape tank_shape_;
    /**
     * @brief Get new rotation angle for tank shape using mouse position
     * 
     * @param window
     * @return the angle as float
     */
    float GetRotationAngle(sf::RenderWindow &window);

};