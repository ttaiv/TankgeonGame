#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include "Projectile.hpp"
#include "Tank.hpp"
#include "Wall.hpp"
#include "Spike.hpp"

class PlayerTank: public Tank {
  public:
    PlayerTank(sf::Vector2f initial_pos, float speed_scaler);
    
    void Update(sf::RenderWindow &window, std::vector<Projectile> &projectiles, std::vector<Wall> &walls, std::vector<Spike> &spikes);

    /**
     * @brief Sets has_shield_ to true for the player tank.
     * 
     */
    void setShield();

    /**
     * @brief Sets has_shield_ to false for the player tank.
     * 
     */
    void breakShield();

    /**
     * @brief Returns true if the player tank has a shield, false otherwise.
     * 
     * @return true 
     * @return false 
     */
    bool hasShield() const;

  private:
    /**
     * @brief Get new rotation angle for tank shape using mouse position
     * 
     * @param window
     * @return the angle as float in radians
     */
    sf::Texture textureNoTurret_;
    sf::Texture textureTurret_;
    float GetTurretRotationAngle(sf::RenderWindow &window);

    void UpdateShape(float rotation_angle, std::vector<Wall> &walls, std::vector<Spike> &spikes);

    bool has_shield_;
};