#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Obstacle {
  public:
    
    /**
     * @brief A pure virtual function that tells wether a projectile can pass the obstacle.
     * 
     * @return true 
     * @return false 
     */
    virtual bool IsProjectilePassable() = 0;
    
    /**
     * @brief A pure virtual function that tells that a tank cant pass the obstacle. 
     * 
     * @return false 
     */
    bool IsTankPassable() { return false; }

    /**
     * @brief A pure virtual function that draws the obstacle in the window given as a parameter.
     * 
     * @param window 
     */
    virtual void Draw(sf::RenderWindow &window) const = 0;
};

