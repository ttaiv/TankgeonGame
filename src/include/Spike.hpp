#pragma once
#include "Obstacle.hpp"
#include <cmath>

class Spike: public Obstacle 
{
  public:
    

    

    /**
     * @brief Construct a new Spike object
     * 
     * @param position 
     * @param size 
     */
    Spike(sf::Vector2f position, sf::Vector2f size);

    Spike(const Spike &other);
    Spike& operator=(const Spike &other) = delete;

    /**
     * @brief Tells that a projectile can pass spikes
     *  
     * @return true 
     */
    bool IsProjectilePassable() override;

    /**
     * @brief Draws spikes to window given as a parameter.
     * 
     * @param window 
     */
    void Draw(sf::RenderWindow &window) const override;

    sf::FloatRect GetGlobalBounds() const;
    sf::RectangleShape GetShape() const {return spikeShape_;}
  private:
    sf::Vector2f position_;
    sf::Vector2f size_;
    sf::RectangleShape spikeShape_;
    sf::Texture spikeTexture_;
};