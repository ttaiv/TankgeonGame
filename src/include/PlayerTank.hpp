#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include "Projectile.hpp"
#include "Wall.hpp"
#include "Spike.hpp"
#include "Tank.hpp"

class PlayerTank: public Tank {
  public:
    PlayerTank(sf::Vector2f initial_pos, sf::Vector2f initial_speed);
    void Update(sf::RenderWindow &window, std::vector<Projectile> &projectiles, std::vector<Wall> &walls, std::vector<Spike> &spikes);

  private:
    /**
     * @brief Get new rotation angle for tank shape using mouse position
     * 
     * @param window
     * @return the angle as float in radians
     */
    float GetRotationAngle(sf::RenderWindow &window);
    void UpdateShape(float rotation_angle, std::vector<Wall> &walls, std::vector<Spike> &spikes) override;
};