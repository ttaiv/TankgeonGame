#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include "Projectile.hpp"
#include "Wall.hpp"
#include "Spike.hpp"

class Tank {
  public:
    /**
     * @brief Construct a new Tank object
     * 
     * @param initial position
     * @param base speed of the tank
     */
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
     * @brief Creates and shoots a new projectile
     * 
     * @param vector of projectiles 
     * @param angle as radians
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
     * @param rotation angle for shape as degrees
     * @param vector containing level's walls
     * @param vector containing level's spikes
     *  
     */
    virtual void UpdateShape(float rotation_angle, std::vector<Wall> &walls, std::vector<Spike> &spikes) = 0;
};