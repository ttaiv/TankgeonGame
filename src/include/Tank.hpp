#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "OBB.hpp"

struct LevelData;

class Tank : public sf::Transformable {
  public:
    /**
     * @brief Construct a new Tank object
     * 
     * @param initial position
     * @param base speed of the tank
     */
    Tank(sf::Vector2f initial_pos, float speed_scaler);
    
    const sf::RectangleShape& GetShape() const;

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
    sf::FloatRect getRotatedBoundingBox() const;
    void Shoot(float angle, LevelData &level_data_);
    bool goForward(float margin, LevelData &level_data_);
    bool goBack(float margin, LevelData &level_data_);
    bool turnLeft(float margin, LevelData &level_data_);
    bool turnRight(float margin, LevelData &level_data_);

  protected:
    float speed_scaler_;
    int cooldown_timer_ = 0;
    sf::RectangleShape tank_shape_;
    sf::RectangleShape turret_shape_;
    /**
     * @brief Takes in the planned next position and returns if it's crashing or not. margin parameter is to
     * scale the "hitbox" of the tank accordingly.
     * 
     * @param next_pos 
     * @param walls 
     * @param spikes 
     * @param margin 
     * @return true 
     * @return false 
     */
    bool IsCollided(sf::Vector2f next_pos, float margin, LevelData level_data_) const;
    /**
     * @brief Moves the tank around by updating the shape's position 
     * 
     * @param rotation angle for shape as degrees
     * @param vector containing level's walls
     * @param vector containing level's spikes
     *  
     */
    //virtual void UpdateShape(float rotation_angle, std::vector<Wall> &walls, std::vector<Spike> &spikes) = 0;
};