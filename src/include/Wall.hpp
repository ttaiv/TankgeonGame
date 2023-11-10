#pragma once
#include "Obstacle.hpp"

class Wall: public Obstacle 
{
  public:
    
    /**
     * @brief Construct a new Wall object
     * 
     * @param position 
     * @param size 
     */
    Wall(sf::Vector2f position, sf::Vector2f size);

    /**
     * @brief Tells that a projectile cannot pass a wall
     *  
     * @return false 
     */
    virtual bool IsProjectilePassable() override;

    /**
     * @brief Draws a wall to window given as a parameter.
     * 
     * @param window 
     */
    virtual void Draw(sf::RenderWindow &window) const override;

    sf::RectangleShape GetShape() const;
    
    
  private:
    sf::Vector2f position_;
    sf::Vector2f size_;
    sf::RectangleShape wallShape_;
};