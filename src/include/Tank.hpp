#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include "Projectile.hpp"

class Tank {
  public:
    Tank(sf::Vector2f initial_pos, float speed_scaler);
    
    sf::RectangleShape GetShape() const;

    /**
     * @brief Draws the shape on the window
     * 
     * @param window 
     */
    void Draw(sf::RenderWindow &window) const ;

    /**
     * @brief Update takes care of everything that should be updated.
     * Should update the shape and possible projectiles 
     * 
     * @param window 
     * @param projectiles 
     */
    //virtual void Update(sf::RenderWindow &window, std::vector<Projectile> &projectiles) = 0;
    /**
     * @brief Shoots a projectile
     * 
     * @param projectiles 
     * @param angleAsRadians
     */
    void Shoot(std::vector<Projectile> &projectiles, float angle);

  protected:
    float speed_scaler_;
    sf::RectangleShape tank_shape_;
    int cooldown_timer_;
    sf::RectangleShape turret_shape_;

    /**
     * @brief Moves the tank around by updating the shape's position 
     * 
     * @param rotation_angle 
     */
    virtual void UpdateShape(float rotation_angle) = 0;
};