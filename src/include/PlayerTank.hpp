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

  private:
    /**
     * @brief Get new rotation angle for tank shape using mouse position
     * 
     * @param window
     * @return the angle as float in radians
     */
    float GetTurretRotationAngle(sf::RenderWindow &window);
    void UpdateShape(float rotation_angle, std::vector<Wall> &walls, std::vector<Spike> &spikes) override;
    bool IsCollided(sf::Vector2f next_pos, std::vector<Wall> &walls, std::vector<Spike> &spikes) const;
    sf::Texture textureNoPiippu;

>>>>>>> src/include/PlayerTank.hpp
};